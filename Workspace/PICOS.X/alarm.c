/**********************************************************************/
/*                                                                    */
/* File name: alarm.c                                                 */
/*                                                                    */
/* Since:     2002/09/09                                              */
/*                                                                    */
/* Version:   1.11                                                    */
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
/*   2002/11/11  [XM] Because kernel and services are not             */
/*                    interruptible, add calls to CGI & SGI macros.   */
/*   2003/01/10  [XM] Remove #include <pic....h> directive.           */
/*                    Add INFINITE alarm feature (cycle = 0).         */
/*   2003/01/23  [XM] Add Delay40MHz(unsigned int us).                */
/*   2003/01/26  [XM] Replace fixed SECTIONS by relocatable SECTIONS. */
/*   2003/02/02  [XM] Add forgotten SGI in case of immediate return.  */
/*   2003/08/03  [XM] Added "device.h" include.                       */
/*                                                                    */
/**********************************************************************/

#include "device.h"
#include "pro_man.h"
#include "alarm.h"

/**********************************************************************
 * Shared variables defined in other section.
 **********************************************************************/
extern char id_tsk_run;

/**********************************************************************
 * RAM area of the alarm manager.
 **********************************************************************/
#pragma		udata	ALARM_RAM
int* tmp_alarm;
AlarmRefObject liste_alarm;
AlarmRefObject alarm_ptr;

//Aici am declarat alarma
//AlarmRefObject 
/**********************************************************************
 * RAM area of the alarm manager.
 **********************************************************************/
#pragma		code	ALARM_ROM

/**********************************************************************
 * Build a chained list with pointer on alarm structures.
 *
 * @param a_alarm    IN  Reference of the new alarm
 * @return status    Always E_OK 
 **********************************************************************/
StatusType DeclarAlarm(AlarmRefObject al)
{
    
}
StatusType DeclarAlarm(AlarmRefObject a_alarm)
{
  char i;

  CGI;

  alarm_ptr = liste_alarm;
  i = 0;

  if (liste_alarm == NULL)
  {
    liste_alarm = a_alarm;
    liste_alarm->next = NULL;
    liste_alarm->ID = (id_tsk_run << 4);
    SGI;
    return (E_OK);
  }

  while (alarm_ptr->next != NULL)
  {
    alarm_ptr = (AlarmRefObject)(alarm_ptr->next);
    i ++;
  }

  /* We need a TEMP pointer to avoid bugs from compiler */
  tmp_alarm = (int*)&(alarm_ptr->next);
  *tmp_alarm = (int)a_alarm;
  a_alarm->ID = (id_tsk_run << 4) + i + 1;
  a_alarm->flag = 0;

  SGI;
  return (E_OK);
}

/**********************************************************************
 * Program an alarm in relative mode with a number of tick to run from 
 * the current count value.
 *
 * @param ID         IN  ID of the alarm to update 
 * @param increment  IN  Number of ticks to run
 * @param cycle      IN  Number of cycle to process 
 * @return Status    E_OK if the alarm is not used
 *                   E_OS_STATE if in USED mode
 *                   E_OS_ID if ID is not correct
 **********************************************************************/
StatusType SetRelAlarm(AlarmType ID, TickType increment, TickType cycle)
{
  CGI;
  alarm_ptr = liste_alarm;

  while (alarm_ptr != NULL)
  {
    if (ID == alarm_ptr->ID)
    {
      if (alarm_ptr->flag & USED)
      {
        SGI;
        return (E_OS_STATE);
      }
      alarm_ptr->AlarmTickValue = alarm_ptr->currentTickValue + increment;
      alarm_ptr->cycle = cycle;
      alarm_ptr->flag = alarm_ptr->flag | USED;
      alarm_ptr->gap = increment;
      if (cycle == 0)
        alarm_ptr->flag = alarm_ptr->flag | INFINITE;			
      SGI;
      return (E_OK);
    }
    alarm_ptr = alarm_ptr->next;
  }

  SGI;	
  return (E_OS_ID);
}

/**********************************************************************
 * Program an alarm in absolute mode with a number of tick to run from 
 * the start count value.
 *
 * @param ID         IN  ID of the alarm to update 
 * @param start      IN  Nb of ticks to run from start
 * @param cycle      IN  Number of cycle to process 
 * @return Status    E_OK if the alarm is not used
 *                   E_OS_STATE if in used mode
 *                   E_OS_ID if ID is not correct
 **********************************************************************/
StatusType SetAbsAlarm(AlarmType ID, TickType start, TickType cycle)
{
  CGI;
  alarm_ptr = liste_alarm;

  while (alarm_ptr != NULL)
  {
    if (ID == alarm_ptr->ID)
    {
      if (alarm_ptr->flag & USED)
      {
        SGI;
        return (E_OS_STATE);
      }
      alarm_ptr->AlarmTickValue = start;
      alarm_ptr->cycle = cycle;
      alarm_ptr->flag = alarm_ptr->flag | USED;
      if (cycle == 0)
        alarm_ptr->flag = alarm_ptr->flag | INFINITE;
      SGI;
      return (E_OK);
    }
    alarm_ptr = alarm_ptr->next;
  }

  SGI;
  return (E_OS_ID);
}

/**********************************************************************
 * Give the number of tick to run to set the alarm.
 *
 * @param ID         IN  ID of the alarm to update 
 * @param Tick       IN  Reference of tick number
 * @return Status    E_OK if the alarm is in USED mode
 *                   E_OS_NOFUNC if not used
 *                   E_OS_ID if ID is not correct
 **********************************************************************/
StatusType GetAlarm(AlarmType ID, TickRefType Tick)
{
  CGI;
  alarm_ptr = liste_alarm;

  while (alarm_ptr != NULL)
  {
    if (ID == alarm_ptr->ID)
    {
      if ((alarm_ptr->flag & USED) == 0)
      {
        SGI;
        return (E_OS_NOFUNC);
      }
      *Tick = alarm_ptr->AlarmTickValue - alarm_ptr->currentTickValue;
      SGI;
      return (E_OK);
    }
    alarm_ptr = alarm_ptr->next;
  }

  SGI;
  return (E_OS_ID);
}

/**********************************************************************
 * Set the alarm in UNUSED mode.
 *
 * @param ID         IN  ID of the alarm to update
 * @return Status    E_OK if the alarm is in USE mode
 *                   E_OS_NOFUNC if not used
 *                   E_OS_ID if ID is not correct
 **********************************************************************/
StatusType CancelAlarm(AlarmType ID)
{
  CGI;
  alarm_ptr = liste_alarm;

  while (alarm_ptr != NULL)
  {
    if (ID == alarm_ptr->ID)
    {
      if ((alarm_ptr->flag & USED) == 0)
      {
        SGI;
        return (E_OS_NOFUNC);
      }
      alarm_ptr->flag = alarm_ptr->flag & (~USED);
      SGI;
      return (E_OK);
    }
    alarm_ptr = alarm_ptr->next;
  }

  SGI;
  return (E_OS_ID);
}

/**********************************************************************
 * Give the info relative to Alarm Base.
 *
 * @param ID         IN  ID of the alarm to update
 * @param Info       IN  Reference to the alarm base 
 * @return Status    E_OK if the ID is correct
 *                   E_OS_ID if not
**********************************************************************/
StatusType GetAlarmBase(AlarmType ID, AlarmBaseRefType Info)
{
  CGI;
  alarm_ptr = liste_alarm;

  while (alarm_ptr != NULL)
  {
    if (ID == alarm_ptr->ID)
    {
      Info = &(alarm_ptr->base);
      SGI;
      return (E_OK);
    }
    alarm_ptr = alarm_ptr->next;
  }

  SGI;
  return (E_OS_ID);
}

/**********************************************************************
 * Set the ACTION (ACTIVATETASK/SETEVENT) and TYPE (TIMER/COUNTER) to
 * the alarm.
 *
 * @param ID         IN  ID of the alarm to update
 * @param Action     IN  Attach alarm to TASK or EVENT
 * @param Type       IN  Specify COUNTER or TIMER mode
 * @return Status    E_OK if the alarm is not used
 *                   E_OS_STATE if in USED mode
 *                   E_OS_ID if ID is not correct
**********************************************************************/
StatusType SetAlarmAction(AlarmType ID, char Action, char Type)
{
  CGI;
  alarm_ptr = liste_alarm;

  while (alarm_ptr != NULL)
  {
    if (ID == alarm_ptr->ID)
    {
      if (alarm_ptr->flag & USED)
      {
        SGI;
        return (E_OS_STATE);
      }
      alarm_ptr->flag = alarm_ptr->flag + Action + Type;
      SGI;
      return (E_OK);
    }
    alarm_ptr = alarm_ptr->next;
  }

  SGI;
  return (E_OS_ID);
}

/**********************************************************************
 * Specify the ID of the task to attach in case of alarm with 
 * ACTIVATETASK mode.
 *
 * @param ID         IN  ID of the alarm to update
 * @param TaskID     IN  ID of task to attach
 * @return Status    E_OK if the alarm is not used
 *                   E_OS_STATE if in USED mode
 *                   E_OS_ID if ID is not correct
**********************************************************************/
StatusType SetAlarmTarget(AlarmType ID, TaskType TaskID)
{
  CGI;
  alarm_ptr = liste_alarm; 

  while (alarm_ptr != NULL)
  {
   if (ID == alarm_ptr->ID)
   {
     if (alarm_ptr->flag & USED)
     {
       SGI;
       return (E_OS_STATE);
     }
     alarm_ptr->ID &= 0x0F;
     alarm_ptr->ID += (TaskID << 4);
     SGI;
     return (E_OK);
   }
   alarm_ptr = alarm_ptr->next;
  }

  SGI;
  return (E_OS_ID);
}

/**********************************************************************
 * Increment the counter in case of alarm with COUNTER mode.
 *
 * @param ID         IN  ID of the alarm to update
 * @return Status    E_OK if the ID is correct
 *                   E_OS_ID if ID is not correct
**********************************************************************/
StatusType IncCounter(AlarmType ID)
{
  CGI;
  alarm_ptr = liste_alarm;

  while (alarm_ptr != NULL)
  {
    if (ID == alarm_ptr->ID)
    {
      alarm_ptr->currentTickValue++;
      SGI;
      return (E_OK);
    }
    alarm_ptr = alarm_ptr->next;
  }

  SGI;
  return (E_OS_ID);
}

/*********************************************************************
 * Give the current number of tick of the alarm in COUNTER mode. 
 * Work also with alarm in TIMER mode.
 *
 * @param ID         IN  ID of the alarm to update 
 * @param Tick       IN  Reference of tick number
 * @return Status    E_OK if ID is correct
 *                   E_OS_ID if not correct
**********************************************************************/
StatusType GetCounterValue(AlarmType ID, TickRefType tick)
{
  CGI;
  alarm_ptr = liste_alarm;

  while (alarm_ptr != NULL)
  {
    if (ID == alarm_ptr->ID)
    {
      *tick = alarm_ptr->currentTickValue;
      SGI;
      return (E_OK);
    }
    alarm_ptr = alarm_ptr->next;
  }

  SGI;
  return (E_OS_ID);
}

/*********************************************************************
 * Enter in critical region just the time needed in microsecondes.
 *
 * @param us         IN  time from 0 to 65535 us
 * @return Status    E_OK
 *********************************************************************/
StatusType Delay40MHz(unsigned int us)
{
  CGI;

  while(us)
  {
    us = us - 0x01;	 
  }

  SGI;
  return (E_OK);
}
