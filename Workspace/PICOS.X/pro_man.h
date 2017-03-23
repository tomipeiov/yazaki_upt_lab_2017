/**********************************************************************/
/*                                                                    */
/* File name: pro_man.h                                               */
/*                                                                    */
/* Since:     2002/09/09                                              */
/*                                                                    */
/* Version:   1.11                                                    */
/*                                                                    */
/* Author:    MONTAGNE Xavier [XM] {link xavier.montagne@wanadoo.fr}  */
/*                                                                    */
/* Purpose:   Definition of all the types, defines and functions      */
/*            used by the process manager.                            */
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
/*   2003/01/10  [XM] Add #include <pic....h> directive.              */
/*   2003/01/26  [XM] Replace fixed SECTIONS by relocatable SECTIONS. */
/*   2003/02/02  [XM] Add DeclareRAM(RamStartAddress) macro.          */
/*   2003/02/12  [XM] Change CGI/SGI to allow services call from ISR. */
/*   2003/05/10  [XM] Added STATUS register storage in SAVE_TASK_CTX. */
/*                    Added BSR    register storage in CGI.           */
/*   2003/08/03  [XM] Remove the #include <p18f452.h>.                */
/*                                                                    */
/**********************************************************************/

#ifndef _PRO_MAN_H_
#define _PRE_MAN_H_

#pragma		udata	PROC_RAM

/*****************************************************
 * ----------------- Type definition -----------------
 ****************************************************/
typedef rom const struct _rom_desc_tsk
{
	char prioinit;
	char stackinit;
	void (*addr_ROM)(void);
	char futur_use;
	char id_tch;
	int  ctx_tch;
} rom_desc_tsk;

typedef struct _ctx_tsk
{
	char ctx_WREG;
	char ctx_BSR;
	char ctx_STATUS;
	char ctx_FSR0H;
	char ctx_FSR0L;
	char ctx_FSR1H;
	char ctx_FSR1L;
	char ctx_FSR2H;
	char ctx_FSR2L;
	char ctx_PRODH;
	char ctx_PRODL;
} ctx_tsk;

typedef char TaskType;
typedef char *TaskRefType;
typedef char TaskStateType;
typedef char *TaskStateRefType;

typedef char StatusType;
typedef char AppModeType;

/*****************************************************
 * ---------------- Global variables -----------------
 ****************************************************/
extern char id_tsk_run;
extern char call_from;
extern void _sched(void);
extern void _save_ctx(void);
extern char TOSU_SAVE;
extern char TOSH_SAVE;
extern char TOSL_SAVE;
extern char STATUS_save;
extern char BSR_save;

/*****************************************************
 * -------------------- Defines ----------------------
 ****************************************************/
/* -------------------- Macro --------------------- */
#define TASK(TaskName) void TaskName(void)
#define DeclareTask(TaskIdentifier)	extern TASK(TaskIdentifier)
#define DeclareRAM(RamStartAddress) extern ctx_tsk RamStartAddress

#define SAVE_TASK_CTX\
			STATUS_save = STATUS; \
            TOSU_SAVE = TOSU; \
            TOSH_SAVE = TOSH; \
            TOSL_SAVE = TOSL; \
            STKPTR--; \
            _save_ctx(); \
            Save_STKPTR(); \
            _asm \
            movlb   0x00 \
            incf    STKPTR, 1, 0 \
            movf    TOSU_SAVE, 0, 1 \
            movwf   TOSU, 0 \
            movf    TOSH_SAVE, 0, 1 \
            movwf   TOSH, 0 \
            movf    TOSL_SAVE, 0, 1 \
            movwf   TOSL, 0 \
            _endasm

#define SCHEDULE	_asm	goto _sched	_endasm

#define USER        0x00
#define KERNEL      0x01
#define SERVICES    0x02

#define CGI\
            INTCONbits.GIE = 0; \
            _asm movff BSR, BSR_save _endasm \
            if (call_from & SERVICES) \
              _asm bcf call_from, 1, 1 _endasm \
            else \
              _asm bsf call_from, 1, 1 _endasm

#define SGI\
            if (call_from & SERVICES) \
            { \
              call_from = KERNEL; \
              INTCONbits.GIE = 1; \
              call_from = USER; \
              _asm movff BSR_save, BSR _endasm \
            } \
            else \
            { \
              _asm bsf call_from, 1, 1 _endasm \
            }

/* -------- Error returned by OS services --------- */ 
#define E_OK            0x00
#define E_OS_ACCESS     0x01
#define E_OS_CALLEVEL   0x02
#define E_OS_ID         0x03
#define E_OS_LIMIT      0x04
#define E_OS_NOFUNC     0x05
#define E_OS_RESOURCE   0x06
#define E_OS_STATE      0x07
#define E_OS_VALUE      0x08

#define INVALID_TASK    0x10

/* --------------- General defines ---------------- */
#define FALSE           0x00
#define TRUE            0x01
#define AUTO            0x00
#define DISABLE         0x00
#define ENABLE          0x01
#define MIN_TASK_NB     0x00
#define MAX_TASK_NB     0x08

/* ----------------- Task states ------------------ */
#define SUSPENDED       0x00
#define READY           0x01
#define	RUNNING         0x02
#define WAITING         0x04
#define EXTENDED        0x08


/*****************************************************
 * --------------- From pro_man.c file ---------------
 ****************************************************/
void Save_STKPTR(void);

StatusType GetTaskID (TaskRefType TaskID);
StatusType GetTaskState (TaskType TaskID, TaskStateRefType State);
StatusType ActivateTask (TaskType TaskID);
StatusType TerminateTask (void);
StatusType ChainTask (TaskType TaskID);
StatusType Schedule(void);

AppModeType GetActiveApplicationMode(void);
void StartOS(AppModeType Mode);
void ShutdownOS(StatusType Error);

#endif /* _PRO_MAN_H */
