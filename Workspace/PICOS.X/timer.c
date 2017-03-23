/**********************************************************************/
/*                                                                    */
/* File name: timer.c                                                 */
/*                                                                    */
/* Since:     2002/09/09                                              */
/*                                                                    */
/* Version:   1.11                                                    */
/*                                                                    */
/* Author:    MONTAGNE Xavier [XM] {link xavier.montagne@wanadoo.fr}  */
/*                                                                    */
/* Purpose:   Parse the chained list of alarms and update the alarms, */
/*            so activate a task or set an event if necessary.        */
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
/*   2002/11/10  [XM] SETEVENT condition modified :                   */
/*               "if (alarm_ptr->flag > 1)" changed by                */
/*               "if (alarm_ptr->flag & ACTIVATETASK)"                */
/*   2002/11/11  [XM] Because kernel and services are not             */
/*                    interruptible, add calls to CGI & SGI macros.   */
/*   2003/01/10  [XM] Remove #include <pic....h> directive.           */
/*                    Add INFINITE alarm feature (cycle = 0).         */
/*                    Modify TMR0 value to match a periode of 1 ms.   */
/*   2003/01/26  [XM] Replace fixed SECTIONS by relocatable SECTIONS. */
/*   2003/03/10  [XM] Event is no more cleared if already waited.     */
/*   2003/05/10  [XM] Fixed a bug in the while loop for multiple      */
/*                    alarms with the same delay.                     */
/*   2003/08/03  [XM] Added "device.h" include.                       */
/*                                                                    */
/**********************************************************************/

#include "device.h"
#include "pro_man.h"
#include "even_man.h"
#include "alarm.h"
#include "int_man.h"

/**********************************************************************
 * Shared variables defined in other section.
 **********************************************************************/
extern TaskType         tsk_1_stack;
extern TaskType         tsk_1_state;
extern EventMaskType 	wait_1;
extern EventMaskType 	event_1;
extern AlarmRefObject 	liste_alarm;


/**********************************************************************
 * RAM area of the alarm mangement.
 **********************************************************************/
#pragma		udata	COUNTER_RAM

/**********************************************************************
 * ROM area of the alarm mangement.
 **********************************************************************/
#pragma 	code	COUNTER_ROM

/**********************************************************************
 * Parse the chained list of alarms (timer & counter).
 * Increment timer only.
 * Check if alarm event has to be treated according to AlarmTickValue 
 * and CurrentTickValue.
 * Do it for number of cycle positive or null.
 * Check if a task or event has to be activated. 
 * If a task is waiting the event, clear the event and wait flags 
 * (cf event.c) and set the task READY.
 * Call the SCHEDULER at the end.
 *
 * @return void 
 **********************************************************************/
ISR(AddOneTick)
{
  TaskRefType ptr_task;
  TaskType temp;
  char i;
  AlarmRefObject alarm_ptr;

  CGI;
  SAVE_TASK_CTX;

  /* For Timer0 = 1ms with prescaler = 1/8 - Freq = 40MHz*/
  TMR0L += 0x64;

  alarm_ptr = liste_alarm;

  while (alarm_ptr != NULL)
  {
    ptr_task = (TaskRefType)&tsk_1_state;

    if (alarm_ptr->flag & CLOCKED)
      alarm_ptr->currentTickValue ++;
    
    if ((alarm_ptr->currentTickValue == alarm_ptr->AlarmTickValue) &&
        (alarm_ptr->flag & USED) ) /*  (alarm_ptr->flag & CLOCKED) ) */
    {
      if (alarm_ptr->flag & INFINITE)
        alarm_ptr->cycle = 2; 
      alarm_ptr->cycle--;		
      if (alarm_ptr->cycle == 0)
        alarm_ptr->flag = alarm_ptr->flag & (~USED); /* no more in use */					
      alarm_ptr->AlarmTickValue += alarm_ptr->gap;

      for (i = 0; i < 8; i++)
      {
        temp = *ptr_task;
        temp = (temp & 0xF0) >> 4;

        if ( temp == ( (alarm_ptr->ID) & 0xF0 ) >> 4 )
        {
          ptr_task = &wait_1 + i;
          if (alarm_ptr->flag & ACTIVATETASK) /* ACTIVATETASK is set */
          {
            ptr_task = &tsk_1_state + i;
            *ptr_task &= 0xF0;
            *ptr_task += READY;
          }
          else   /* SETEVENT is set */
          {
            ptr_task = &event_1 + i;
            *ptr_task |= ALARM_EVENT;
            ptr_task = &wait_1 + i;

            /* A task is waiting for at least one event */
            if (*ptr_task & ALARM_EVENT)
            {			
              ptr_task = &tsk_1_state + i;
              *ptr_task &= 0xF0;
              *ptr_task += READY;
            }
          }
        }
        ptr_task++;
      }
    }
    alarm_ptr = (AlarmRefObject)alarm_ptr->next;
  }

  INTCONbits.TMR0IF = 0;
  STKPTR--;
  SCHEDULE;
}

