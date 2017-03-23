/**********************************************************************/
/*                                                                    */
/* File name: even_man.h                                              */
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
/*      2002/09/09  [XM] Create this file.                            */
/*   2003/01/26  [XM] Replace fixed SECTIONS by relocatable SECTIONS. */
/*                                                                    */
/**********************************************************************/

#ifndef _EVEN_MAN_h_
#define _EVEN_MAN_h_

/*****************************************************
 * ----------------- Type definition -----------------
 ****************************************************/
typedef char  EventMaskType;
typedef char *EventMaskRefType;

/*****************************************************
 * -------------------- Defines ----------------------
 ****************************************************/
/* ----- Value reserved for Alarm event only ------ */
#define ALARM_EVENT		0x80

/*****************************************************
 * --------------- From even_man.c file ---------------
 ****************************************************/
StatusType SetEvent(TaskType TaskID, EventMaskType Mask);
StatusType ClearEvent(EventMaskType Mask);
StatusType GetEvent(TaskType TaskID, EventMaskRefType Mask);
StatusType WaitEvent(EventMaskType Mask);

#endif /* _EVEN_MAN_h_ */



