/**********************************************************************/
/*                                                                    */
/* File name: alarm.h                                                 */
/*                                                                    */
/* Since:     2002/09/09                                              */
/*                                                                    */
/* Version:   1.11                                                     */
/*                                                                    */
/* Author:    MONTAGNE Xavier [XM] {link xavier.montagne@wanadoo.fr}  */
/*                                                                    */
/* Purpose:   The alarm manager is in charge of setting the           */
/*            alarm-timers or updating the alarm-counter from         */
/*            application layer.                                      */
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
/*   2002/11/02  [XM] MPLAB-C18 is not able to compute typedef        */
/*                    struct in the same line.                        */
/*   2003/01/26  [XM] Replace fixed SECTIONS by relocatable SECTIONS. */
/*                                                                    */
/**********************************************************************/

#ifndef _ALARM_H_
#define _ALARM_H_

/*****************************************************
 * -------------------- Defines ----------------------
 ****************************************************/
#define NULL               0x00
#define USED               0x01
#define ACTIVATETASK       0x02
#define SETEVENT           0x00
#define CLOCKED            0x04
#define NOT_CLOCKED        0x00
#define INFINITE           0x08
#define BASIC              0x00

/*****************************************************
 * ----------------- Type definition -----------------
 ****************************************************/
typedef int  TickType;
typedef int *TickRefType;
typedef char AlarmType;
typedef char AlarmRefType;

struct _AlarmBaseType
{
	char maxAllowedValue;
	char ticksPerBase;
	char minCycle;
};

typedef struct _AlarmBaseType   AlarmBaseType;
typedef struct _AlarmBaseType * AlarmBaseRefType;

struct _AlarmObject
{
	AlarmType ID; /*4 bits de taskID, 4 bits de AlarmID*/
	/*flag =  0x00000 CYCLES(INFINITE,BASIC)
	                  TYPE(CLOCKED/NOT_CLOCKED)
	                  ACTION(ACTIVATETESK/SETEVENT) 
	                  USED(TRUE/FALSE) */
	char flag; 
	TickType AlarmTickValue;
	TickType currentTickValue;
	TickType gap; 
	char cycle;
	AlarmBaseType base;
	struct _AlarmObject * next;
};

typedef struct _AlarmObject   AlarmObject;
typedef struct _AlarmObject * AlarmRefObject;

/*****************************************************
 * ---------------- From alarm.c file ----------------
 ****************************************************/
StatusType DeclarAlarm(AlarmRefObject a_alarm);
StatusType SetRelAlarm(AlarmType ID, TickType increment, TickType cycle);
StatusType SetAbsAlarm(AlarmType ID, TickType start, TickType cycle);
StatusType GetAlarm(AlarmType ID, TickRefType Tick);
StatusType CancelAlarm(AlarmType ID);
StatusType GetAlarmBase(AlarmType ID, AlarmBaseRefType Info);
StatusType SetAlarmAction(AlarmType ID, char Action, char Type);
StatusType SetAlarmTarget(AlarmType ID, TaskType TaskID);
StatusType IncCounter(AlarmType ID);
StatusType GetCounterValue(AlarmType ID, TickRefType tick);
StatusType Delay40MHz(unsigned int us);

#define GetAlarmID(AlarmName)     AlarmName.ID

#endif /* _ALARM_H_ */

