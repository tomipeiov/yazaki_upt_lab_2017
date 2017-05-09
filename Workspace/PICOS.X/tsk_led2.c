/**********************************************************************/
/*                                                                    */
/* File name: tsk_led.c                                               */
/*                                                                    */
/* Since:     2002/10/09                                              */
/*                                                                    */
/* Version:   1.11                                                    */
/*                                                                    */
/* Author:    MONTAGNE Xavier [XM] {link xavier.montagne@wanadoo.fr}  */
/*                                                                    */
/* Purpose:   This task is void.                                      */
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
/*   2002/10/27  [XM] Create this file.                               */
/*   2003/01/10  [XM] Remove #include <pic....h> directive.           */
/*   2003/01/26  [XM] Replace fixed SECTIONS by relocatable SECTIONS. */
/*   2003/08/03  [XM] Added "device.h" include.                       */
/*               [XM] Added STACK_SIZE label to adjust the temp area  */
/*                    size of each task (according to C18 .tempdata). */
/*                                                                    */
/**********************************************************************/

#include "device.h"
#include "pro_man.h"
#include "even_man.h"
#include "task.h"

/**********************************************************************
 * Definition dedicated to the local functions.
 **********************************************************************/


/**********************************************************************
 * RAM area of the task.
 * Context area first followed by software stack area.
 **********************************************************************/
#pragma		udata	LED_BL_RAM
/* Always context task area before */
ctx_tsk ctx_led_bl;
char stack_led_bl[16];
char done;
/**********************************************************************
 * ---------------------------- Led_ON TASK ---------------------------
 *
 * void
 *
 **********************************************************************/
#pragma		code	LED_BL_ROM
int taskCounter;
unsigned int counter;
ctx_tsk ctx_man;
TASK(Led_blinking)
{
//   if (done == 0)
//   {
//      PORTEbits.RE1 = 1;
//      done = 1;
//   }
//   else
//   {
//      PORTEbits.RE1 = 0;
//      done = 0;
//   }
//
//   counter++;
//   if (counter == 4)
//   {
//      SetEvent(LEDEVENT, LED_EVENT);
//      counter = 0;
//   }
    taskCounter++;
    if(taskCounter >= 4){
        ActivateTask(Task_MAN);
        taskCounter = 0;
    }
   TerminateTask();
}
 
TASK(Man)
{
    TerminateTask();
}

