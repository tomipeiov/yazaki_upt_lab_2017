/**********************************************************************/
/*                                                                    */
/* File name: pro_man.c                                               */
/*                                                                    */
/* Since:     2002/09/09                                              */
/*                                                                    */
/* Version:   1.11                                                    */
/*                                                                    */
/* Author:    MONTAGNE Xavier [XM] {link xavier.montagne@wanadoo.fr}  */
/*                                                                    */
/* Purpose:   The process manager is in charge of changing or giving  */
/*            the state of the different tasks, and also of starting  */
/*            or stopping the kernel.                                 */
/*                                                                    */
/* Distribution: This file is part of PICOS18                         */
/*               PICOS18 is free software; you can redistribute it    */
/*               and/or modify it under the terms of the GNU General  */
/*               Public License as published by the Free Software     */
/*               Foundation; either version 2, or (at your option)    */
/*               any later version.                                   */
/*                                                                    */
/*               PICOS18 is distributed in the hope that it will be   */
/*               useful, but WITHOUT ANY WARRANTY; without even the   */
/*               implied warranty of MERCHANTABILITY or FITNESS FOR A */
/*               PARTICULAR PURPOSE.  See the GNU General Public      */
/*               License for more details.                            */
/*                                                                    */
/*               You should have received a copy of the GNU General   */
/*               Public License along with gpsim; see the file        */
/*               COPYING.txt. If not, write to the Free Software      */
/*               Foundation, 59 Temple Place - Suite 330,             */
/*               Boston, MA 02111-1307, USA.                          */
/*                                                                    */
/* History:                                                           */
/*   2002/09/09  [XM] Create this file.                               */
/*   2002/11/11  [XM] Because kernel and services are not             */
/*                    interruptible, add calls to CGI & SGI macros.   */
/*   2003/01/10  [XM] Remove #include <pic....h> directive.           */
/*   2003/01/26  [XM] Replace fixed SECTIONS by relocatable SECTIONS. */
/*   2003/02/02  [XM] Add forgotten SGI in case of immediate return.  */
/*   2003/02/12  [XM] Modify Save_STKPTR to call services from ISR.   */
/*   2003/05/10  [XM] Modify Save_STKPTR to avoid stack usage.        */
/*   2003/08/03  [XM] Modify TerminateTask and ChainTask  to restore  */
/*                    orginal task address properly.                  */
/*                    Added "device.h" include.                       */
/*                                                                    */
/**********************************************************************/

#include "device.h"
#include "pro_man.h"
#include "INT_man.h"

/**********************************************************************
 * Shared variables defined in other section.
 **********************************************************************/
extern TaskRefType ptr_task;
extern TaskType temp;
extern char i;
extern char id_tsk_run;
extern char call_from;

/**********************************************************************
 * Functions declared in other sections.
 **********************************************************************/
#ifdef	SHUTDOWNHOOK
	extern void ShutdownHook(StatusType Error);
#endif

#ifdef	ERRORHOOK
	extern void ErrorHook(StatusType Error);
#endif

extern void _kernel(void);
extern void _restore_start_adr(void);

/**********************************************************************
 * RAM area of the stack field of a task.
 **********************************************************************/
#pragma		udata	STACK_RAM=0x00A0
TaskType tsk_1_stack;
TaskType tsk_2_stack;
TaskType tsk_3_stack;
TaskType tsk_4_stack;
TaskType tsk_5_stack;
TaskType tsk_6_stack;
TaskType tsk_7_stack;
TaskType tsk_8_stack;

/**********************************************************************
 * RAM area of the state field of the task.
 **********************************************************************/
#pragma		udata	STATE_RAM=0x00A8
TaskType tsk_1_state;
TaskType tsk_2_state;
TaskType tsk_3_state;
TaskType tsk_4_state;
TaskType tsk_5_state;
TaskType tsk_6_state;
TaskType tsk_7_state;
TaskType tsk_8_state;

/**********************************************************************
 * RAM area of the process manager.
 **********************************************************************/
#pragma		udata	PROC_RAM
char TOSU_SAVE;
char TOSH_SAVE;
char TOSL_SAVE;
char TOSU_MAIN;
char TOSH_MAIN;
char TOSL_MAIN;
char appmode;


/**********************************************************************
 * ROM area of the process manager.
 **********************************************************************/
#pragma		code	PROC_ROM

/**********************************************************************
 * Save the stack pointer adress into tsk_*_stack.
 *
 * @return void 
 **********************************************************************/
void Save_STKPTR(void)
{
  if (call_from != SERVICES)
    return;

  ptr_task = &tsk_1_state;
  //for (i = 0; i < 8; i++)
  while(ptr_task <= &tsk_8_state)
  {
    temp = *ptr_task;
    temp &= 0xF0;
    temp = temp >> 4;

    if ( temp == id_tsk_run )
    {
      ptr_task = ptr_task - 8;
      *ptr_task &= 0xE0;
      *ptr_task += (STKPTR & 0x1F);
      break;
    }
    ptr_task++;
  }
  return;
}

/**********************************************************************
 * Modify the priority of a task.
 * Not mandatory by OSEK standart.
 *
 * @param new_prio   IN  Futur prio of the task 
 * @param id_task    IN  ID of the task
 * @return void 
 **********************************************************************/
/*
void 	SetPriority (char new_prio, char id_task)
{
  char *ptr_task;
  char i, temp;

  ptr_task = &tsk_1_state;

  for (i = 0; i < 8; i++)
  {
    temp = *(ptr_task + i);
    temp = (temp & 0xF0) >> 4;

    if ( temp == id_task )
    {
      ptr_task = &tsk_1_stack + i;
      new_prio = new_prio << 5;
      *ptr_task &= 0x1F;
      *ptr_task += new_prio;
      break;
    }
  }

  _ordo();

  return;
}
*/

/**********************************************************************
 * Set id_tsk_run into TaskID or INVALID_TASK (0x10) if the ID is out 
 * of range.
 *
 * @param TaskID     IN  Reference of the task
 * @return status    Always E_OK 
 **********************************************************************/
StatusType GetTaskID (TaskRefType TaskID)
{
  CGI;
  if ( (id_tsk_run > MIN_TASK_NB) && (id_tsk_run < MAX_TASK_NB) )
    *TaskID = (TaskType)id_tsk_run;
  else
    *TaskID = (TaskType)INVALID_TASK;

  SGI;
  return (E_OK);
}

/**********************************************************************
 * Copy a byte into a buffer.
 *
 * @param TaksID     IN  ID of the task 
 * @param State      OUT Reference of the task state
 * @return Status    E_OK if the task ID is correct
 *                   E_OS_ID otherwise
 **********************************************************************/
StatusType GetTaskState (TaskType TaskID, TaskStateRefType State)
{
  CGI;
  ptr_task = (TaskRefType)&tsk_1_state;

  for (i = MIN_TASK_NB; i < MAX_TASK_NB; i++)
  {
    temp = *ptr_task;
    temp = (temp & 0xF0) >> 4;

    if ( temp == TaskID )
    {
      temp = *ptr_task & 0x0F;
      *State = (TaskStateType)temp;
      SGI;
      return (E_OK);
    }
    ptr_task++;
  }

  SGI;
  return (E_OS_ID);
}

/**********************************************************************
 * Set the task to the READY state and call the scheduler to jump to 
 * another task if necessary.
 *
 * @param TaskID     IN  ID of the task
 * @return Status    E_OS_ID if ID is not correct
 *                   never return otherwise
 **********************************************************************/
StatusType ActivateTask (TaskType TaskID)
{
  CGI;
  SAVE_TASK_CTX;

  ptr_task = (TaskRefType)&tsk_1_state;

  for (i = MIN_TASK_NB; i < MAX_TASK_NB; i++)
  {
    temp = *ptr_task;
    temp = (temp & 0xF0) >> 4;

    if ( temp == TaskID )
    {
      *ptr_task &= 0xF0;
      *ptr_task += READY;
      SCHEDULE;
    }
    ptr_task++;
  }

  SGI;
  return (E_OS_ID);
}

/**********************************************************************
 * Allow a task to terminate itself. Cannot terminate another task.
 * To prepare a new activation of the task, we need first to store in
 * stack the start adress of the task
 *
 * [WARNING - C18 compiler bug] :
 *   To avoid a stack overflow please add a dummy call after the 
 *   TerminateTask call.
 * 
 *   For example : 
 *     ...
 *     TerminateTask();
 *     DummyFunct();
 *   }
 *   with DummyFunct :
 * 
 *   void DummyFunct(void)
 *   {
 *	   _asm nop _endasm
 *   }
 *
 * @param dest       OUT Destination buffer 
 * @param src        IN  The byte to copy
 * @return Status    E_OK if ID is not correct
 *                   In fact the function never return 
 **********************************************************************/
StatusType TerminateTask (void)
{
  CGI;
  SAVE_TASK_CTX;
  ptr_task = (TaskRefType)&tsk_1_state;
 
  for (i = MIN_TASK_NB; i < MAX_TASK_NB; i++)
  {
    temp = *ptr_task;
    temp = (temp & 0xF0) >> 4;
 
    if ( temp == id_tsk_run )
    {
      *ptr_task &= 0xF0;
      *ptr_task += SUSPENDED;
/*
      ptr_task = &tsk_1_stack + i;
      STKPTR = *ptr_task & 0x1F;
*/
      _asm goto  _restore_start_adr  _endasm
      /* SCHEDULE is called by _restore_start_adr */
    }
    ptr_task++;
  }
 
  SGI;
  return (E_OK);
}

/**********************************************************************
 * Chain a task by setting the calling task in a SUSPENDED state and 
 * the called taks in the READY state.
 * Call the scheduler to jump the chained task.
 *
 * @param TaskID     IN  ID of the next task to chain
 * @return Status    E_OK if ID is not correct
 *                   In fact the function never return 
 **********************************************************************/
StatusType ChainTask (TaskType TaskID)
{
  CGI;
  SAVE_TASK_CTX;

  ptr_task = (TaskRefType)&tsk_1_state;

  for (i = MIN_TASK_NB; i < MAX_TASK_NB; i++)
  {
    temp = *ptr_task;
    temp = (temp & 0xF0) >> 4;

    if ( temp == id_tsk_run )
    {
      *ptr_task &= 0xF0;
      *ptr_task += SUSPENDED;
    }
    if ( temp == TaskID )
    {
      *ptr_task &= 0xF0;
      *ptr_task += READY;
    }
    ptr_task++;
  }
  
  /*SCHEDULE;*/
  _asm goto  _restore_start_adr  _endasm
  /* SCHEDULE is called by _restore_start_adr */

  SGI;
  return (E_OK);
}

/**********************************************************************
 * Force a scheduler action
 *
 * @return Status    E_OK 
 *                   In fact the function never return 
 **********************************************************************/
StatusType Schedule(void)
{
  CGI;
  SAVE_TASK_CTX;
  SCHEDULE;
  SGI;
  return (E_OK);
}

/**********************************************************************
 * Return the appmode global variable.
 *
 * @return AppMode   The mode set by application 
 **********************************************************************/
AppModeType GetActiveApplicationMode(void)
{
  return(appmode);
}

/**********************************************************************
 * Jump to the KERNEL code area by setting the appmode global variable. 
 * This service is for call from main routine only.
 * Store at first the return adress in main routine.
 *
 * @param Mode       IN  Mode to set into appmode
 * @return void
 **********************************************************************/
void StartOS(AppModeType Mode)
{
  TOSL_MAIN = TOSL;
  TOSH_MAIN = TOSH;
  TOSU_MAIN = TOSU;

  appmode = Mode;
  STKPTR = 0;
  _asm	goto _kernel  _endasm;
}

/**********************************************************************
 * Stop the kernel and task activation after an error occurs. 
 * The function returns to the adress of the main function stored by 
 * the StartOS service.
 *
 * @param error      IN  Last error number detected
 * @return void
 **********************************************************************/
void ShutdownOS(StatusType Error)
{	
#ifdef	SHUTDOWNHOOK
  ShutdownHook(Error);
#endif
  _asm	movf	TOSL_MAIN, 0, 1	_endasm
  _asm	movwf	TOSL, 0		_endasm
  _asm	movf	TOSH_MAIN, 0, 1	_endasm
  _asm	movwf	TOSH, 0		_endasm
  _asm	movf	TOSU_MAIN, 0, 1	_endasm
  _asm	movwf	TOSU, 0		_endasm
  _asm	return  0		_endasm
  _asm	reset			_endasm
}
