/**********************************************************************/
/*                                                                    */
/* File name: main.c                                                  */
/*                                                                    */
/* Since:     2002/09/09                                              */
/*                                                                    */
/* Version:   1.11                                                    */
/*                                                                    */
/* Author:    MONTAGNE Xavier [XM] {link xavier.montagne@wanadoo.fr}  */
/*                                                                    */
/* Purpose:   Initialize the entier RAM and start the kernel.         */
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
/*   2003/01/10  [XM] Remove #include <pic....h> directive.           */
/*   2003/01/26  [XM] Replace fixed SECTIONS by relocatable SECTIONS. */
/*   2003/08/03  [XM] Added "device.h" include.                       */
/*                                                                    */
/**********************************************************************/

#include "device.h"
#include "pro_man.h"
#include "alarm.h"
#include "task.h"

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 128      // Watchdog Timer Postscale Select bits (1:128)

// CONFIG3H
#pragma config CCP2MUX = ON     // CCP2 Mux bit (CCP2 input/output is multiplexed with RC1)

// CONFIG4L
#pragma config STVR = OFF       // Stack Full/Underflow Reset Enable bit (Stack Full/Underflow will not cause RESET)
#pragma config LVP = ON         // Low Voltage ICSP Enable bit (Low Voltage ICSP enabled)

/**********************************************************************
 * Definition dedicated to the local functions.
 **********************************************************************/
#define DEFAULT_MODE       0

/**********************************************************************
 * Function prototypes.
 **********************************************************************/
void main (void);
void Init(void);
void StartupHook(void);
void ShutdownHook(StatusType error);
void ErrorHook(StatusType error);
void PreTaskHook(void);
void PostTaskHook(void);


/**********************************************************************
 * RAM area of the main function.
 * Context area first followed by global variables.
 **********************************************************************/
#pragma		udata	MAIN_RAM
AppModeType SelectedMode;
AlarmObject LedTimer;

/**********************************************************************
 * -------------------------- main function ---------------------------
 *
 * Setup the different alarms and start the kernel.
 *
 **********************************************************************/
#pragma		code	MAIN_ROM

void main(void)
{
  SelectedMode = DEFAULT_MODE;
  Init();
  
  DeclarAlarm(&LedTimer);
  SetAlarmAction(GetAlarmID(LedTimer), ACTIVATETASK, CLOCKED);
  SetAlarmTarget(GetAlarmID(LedTimer), LEDBLINKING);
  SetRelAlarm(GetAlarmID(LedTimer), 10, 0);
  
  while(1)
  {
    StartOS(SelectedMode);
  }
}

/**********************************************************************
 * Clear all RAM memory and set PORTB to output mode.
 *
 * @return void
 **********************************************************************/
void Init(void)
{
  _asm	movlw	0x07		_endasm
  _asm	movwf	ADCON1, 0	_endasm
  _asm	movlw	0x00		_endasm
  _asm	movwf	TRISE, 0	_endasm 

  PORTE = 0;

  FSR0H = 0;
  FSR0L = 0;

  while (FSR0H < 6)
  {
    INDF0 = 0;
    if (FSR0L == 0xFF)
      FSR0H++;
    FSR0L++;
  }
}

/**********************************************************************
 * Hook routine called just before entering in kernel.
 *
 * @param error      IN The new error stored in buffer
 * @return error     Error level
 **********************************************************************/
void StartupHook(void)
{
}

/**********************************************************************
 * Hook routine called just after leaving the kernel.
 *
 * @param error      IN The last error detected by OS
 * @return void
 **********************************************************************/
void ShutdownHook(StatusType error)
{
}

/**********************************************************************
 * Store a new error in a global buffer keeping a track of the 
 * application history.
 *
 * @param error      IN The new error stored in buffer
 * @return void
 **********************************************************************/
void ErrorHook(StatusType error)
{
}

/**********************************************************************
 * Hook routine called just before entering in a task.
 *
 * @return void
 **********************************************************************/
void PreTaskHook(void)
{
}

/**********************************************************************
 * Hook routine called just after leaving a task.
 *
 * @return void
 **********************************************************************/
void PostTaskHook(void)
{
}
