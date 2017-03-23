/**********************************************************************/
/*                                                                    */
/* File name: even_man.c                                              */
/*                                                                    */
/* Since:     2002/09/09                                              */
/*                                                                    */
/* Version:   1.11                                                    */
/*                                                                    */
/* Author:    MONTAGNE Xavier [XM] {link xavier.montagne@wanadoo.fr}  */
/*                                                                    */
/* Purpose:   The event manager is in charge of setting and clearing  */
/*            the events waited by the tasks.                         */
/*            2 areas are used to manage the arrival of events and    */
/*            the fact that some tasks are waiting for these events.  */
/*              - EVENT ram area : for events set by tasks or alarms  */
/*              - WAIT  ram area : for events waited by tasks         */
/*            The job of the event manager is to take care of task    */
/*            activation in case of any similarity inbetween events   */
/*            set and events waited.                                  */
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
/*   2003/08/03  [XM] Added "device.h" include.                       */
/*                                                                    */
/**********************************************************************/

#include "device.h"
#include "pro_man.h"
#include "INT_man.h"
#include "EVEN_man.h"

/**********************************************************************
 * Shared variables defined in other section.
 **********************************************************************/
extern TaskType tsk_1_stack;
extern TaskType tsk_1_state;
extern char     id_tsk_run;

/**********************************************************************
 * RAM area of the events set by the tasks or alarms.
 **********************************************************************/
#pragma		udata	EVENT_MASK=0x0090
EventMaskType event_1;
EventMaskType event_2;
EventMaskType event_3;
EventMaskType event_4;
EventMaskType event_5;
EventMaskType event_6;
EventMaskType event_7;
EventMaskType event_8;

/**********************************************************************
 * RAM area of the events waited by the tasks.
 **********************************************************************/
#pragma		udata	WAIT_MASK=0x0098
EventMaskType wait_1;
EventMaskType wait_2;
EventMaskType wait_3;
EventMaskType wait_4;
EventMaskType wait_5;
EventMaskType wait_6;
EventMaskType wait_7;
EventMaskType wait_8;

/**********************************************************************
 * RAM area of the event manager.
 **********************************************************************/
#pragma		udata	EVEN_RAM=0x0080
TaskRefType ptr_task;
TaskType temp;
char i;

/**********************************************************************
 * ROM area of the event manager.
 **********************************************************************/
#pragma		code	EVEN_ROM

/**********************************************************************
 * Set an event in the EVENT ram area of a task.
 * The event is reset if the task is already waiting for this event 
 * (task set into READY state).
 *
 * @param TaskID     IN  Reference of the task
 * @param Mask       IN  Bitmask of the event to set 
 * @return status    E_OK if no waiting task
 *                   E_OS_STATE if task suspended
 *                   E_OS_ID if ID is not correct
 *                   no return value otherwise
 **********************************************************************/
StatusType SetEvent(TaskType TaskID, EventMaskType Mask)
{
  CGI;
  SAVE_TASK_CTX;

  ptr_task = (TaskRefType)&tsk_1_state;

  for (i = 0; i < 8; i++)
  {
    temp = *ptr_task;
    temp = (temp & 0xF0) >> 4;

    if ( temp == TaskID )
    {
      if ((*ptr_task & 0x0F) == SUSPENDED)
      {
        SGI;
        return (E_OS_STATE);
      }
      ptr_task = &event_1 + i;
      *ptr_task |= Mask;
      ptr_task = &wait_1 + i;

      /* Not any task waiting for at least one event */
      if ( (*ptr_task & Mask) == 0 )
      {
        SGI;
        return (E_OK);
      }
      else
      {
        ptr_task = &tsk_1_state + i;
        *ptr_task &= 0xF0;
        *ptr_task += READY;

        SCHEDULE;
      }
    }
    ptr_task++;
  }

  if (i == 8)
  {
    SGI;
    return (E_OS_ID);
   }

  SGI;
  return (E_OK);
}

/**********************************************************************
 * Clear an event in the EVENT ram area and the WAIT ram area of the
 * calling task.
 * Should be called by a task just after the waitevent service call.
 *
 * @param Mask       IN  Bitmask of the event to set 
 * @return status    Always E_OK
 **********************************************************************/
StatusType ClearEvent(EventMaskType Mask)
{
  CGI;
  ptr_task = (TaskRefType)&tsk_1_state;

  for (i = 0; i < 8; i++)
  {
    temp = *ptr_task;
    temp = (temp & 0xF0) >> 4;

    if ( temp == id_tsk_run )
    {
      ptr_task = &event_1 + i;
      *ptr_task &= ~Mask;
      ptr_task = &wait_1 + i;
      *ptr_task &= ~Mask;
      SGI;
      return (E_OK);
    }
    ptr_task++;
  }

  SGI;
  return (E_OK);
}

/**********************************************************************
 * Get all the event (byte value)from the EVENT ram area of a task.
 * Allow the task to guess from which event it is waked up.
 *
 * @param TaskID     IN  Reference of the task
 * @param Mask       IN  Reference of the event to get 
 * @return status    E_OS_STATE if task suspended
 *                   E_OS_ID if ID is not correct
 *                   E_OK otherwise
 **********************************************************************/
StatusType GetEvent(TaskType TaskID, EventMaskRefType Mask)
{
  CGI;
  ptr_task = (TaskRefType)&tsk_1_state;

  for (i = 0; i < 8; i++)
  {
    temp = *ptr_task;
    temp = (temp & 0xF0) >> 4;

    if ( temp == TaskID )
    {
      if ((*ptr_task & 0x0F) == SUSPENDED)
      {
        SGI;
        return (E_OS_STATE);
      }

      ptr_task = &event_1 + i;
      *Mask = (EventMaskType) *ptr_task;
      SGI;
      return (E_OK);
    }
    ptr_task++;
  }

  if (i == 8)
  {
    SGI;
    return (E_OS_ID);
  }

  SGI;
  return (E_OK);
}

/**********************************************************************
 * Set an event in the WAIT ram area of a task.
 * If the same event is set in the EVENT ram area, the function 
 * immediatly returns. If not the task is set in WAITING state.
 *
 * @param Mask       IN  Bitmask of the event to wait 
 * @return status    E_OK if the event exists
 *                   E_OS_ID if ID is not correct 
 *                   no return value otherwise
 **********************************************************************/
StatusType WaitEvent(EventMaskType Mask)
{
  CGI;
  SAVE_TASK_CTX;

  ptr_task = (TaskRefType)&tsk_1_state;

  for (i = 0; i < 8; i++)
  {
    temp = *ptr_task;
    temp = (temp & 0xF0) >> 4;

    if ( temp == id_tsk_run )
    {
      ptr_task = &wait_1 + i;
      *ptr_task = Mask;
      ptr_task = &event_1 + i;

      /* Not any event waited present */
      if ( (*ptr_task & Mask) == 0 )
      {
        ptr_task = (TaskRefType)&tsk_1_state;
        ptr_task += i;
        *ptr_task += WAITING;

        SCHEDULE;
      }
      else
      {
        SGI;
        return (E_OK);
      }
    }
    ptr_task++;
  }

  if (i == 8)
  {
    SGI;
    return (E_OS_ID);
  }

  SGI;
  return (E_OK);
}

