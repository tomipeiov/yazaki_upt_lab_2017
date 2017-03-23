/**********************************************************************/
/*                                                                    */
/* File name: int_man.c                                               */
/*                                                                    */
/* Since:     2002/09/09                                              */
/*                                                                    */
/* Version:   1.11                                                    */
/*                                                                    */
/* Author:    MONTAGNE Xavier [XM] {link xavier.montagne@wanadoo.fr}  */
/*                                                                    */
/* Purpose:                                                           */
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
#include "INT_man.h"

/**********************************************************************
 * RAM area of the interrupt manager.
 *********************************************************************/
#pragma		udata	INT_RAM

/**********************************************************************
 * ROM area of the interrupt manager.
 *********************************************************************/
#pragma		code	INT_ROM

/**********************************************************************
*                                                                     
*       EnterISR                                                      
*                                                                     
**********************************************************************/
/*void	EnterISR(void)
{
	TaskRefType ptr_task;
	TaskType temp;
	char i;

	INTCONbits.GIE = DISABLE_GIE_INT;

	call_from = ENTER_ISR_Category_3;
	return;
}*/

/**********************************************************************
*                                                                     *
*       LeaveISR                                                      *
*                                                                     *
**********************************************************************/
/*void 	LeaveISR(void)
{
	TaskRefType ptr_task;
	TaskType temp;
	char i;

	call_from = LEAVE_ISR_Category_3;

	INTCONbits.GIE = ENABLE;
	return;
}*/

/**********************************************************************
*                                                                     
*       EnableInterrupt                                               
*                                                                     
**********************************************************************/
StatusType EnableInterrupt(IntDescriptorType Descriptor)
{
  INTCONbits.GIE = 0;

  if (Descriptor & TIMER1_INT)
    PIE1bits.TMR1IE = 1;

  if (Descriptor & TIMER2_INT)
    PIE1bits.TMR2IE = 1;

  if (Descriptor & TIMER3_INT)
    PIE2bits.TMR3IE = 1;

  if (Descriptor & EXTERNAL0_INT)
    INTCONbits.INT0IE = 1;

  if (Descriptor & EXTERNAL1_INT)
    INTCON3bits.INT1IE = 1;
/*
  if (Descriptor & EXTERNAL2_INT)
    INTCON3bits.INT2IE = 1;	
*/
  if (Descriptor & SERIAL_RC_INT)
    PIE1bits.RCIE = 1;	

  if (Descriptor & SERIAL_RC_INT)
    PIE1bits.TXIE = 1;	

  INTCONbits.GIE = 1;
  return (E_OK);
}

/**********************************************************************
*                                                                     
*       DisableInterrupt                                              
*                                                                     
**********************************************************************/
StatusType DisableInterrupt(IntDescriptorType Descriptor)
{
  INTCONbits.GIE = 0;

  if (Descriptor & TIMER1_INT)
    PIE1bits.TMR1IE = 0;

  if (Descriptor & TIMER2_INT)
    PIE1bits.TMR2IE = 0;

  if (Descriptor & TIMER3_INT)
    PIE2bits.TMR3IE = 0;

  if (Descriptor & EXTERNAL0_INT)
    INTCONbits.INT0IE = 0;

  if (Descriptor & EXTERNAL1_INT)
    INTCON3bits.INT1IE = 0;
/*
  if (Descriptor & EXTERNAL2_INT)
    INTCON3bits.INT2IE = 0;	
*/
  if (Descriptor & SERIAL_RC_INT)
    PIE1bits.RCIE = 0;	

  if (Descriptor & SERIAL_RC_INT)
    PIE1bits.TXIE = 0;	

  INTCONbits.GIE = 1;
  return (E_OK);
}

/**********************************************************************
*                                                                     
*       GetInterruptDescriptor                                        
*                                                                     
**********************************************************************/
StatusType GetInterruptDescriptor(IntDescriptorRefType Descriptor)
{
  INTCONbits.GIE = 0;
  Descriptor = 0;

  if (PIE1bits.TMR1IE)
    Descriptor += TIMER1_INT;

  if (PIE1bits.TMR2IE)
    Descriptor += TIMER2_INT;

  if (PIE2bits.TMR3IE)
    Descriptor += TIMER3_INT;

  if (INTCONbits.INT0IE)
    Descriptor += EXTERNAL0_INT;

  if (INTCON3bits.INT1IE)
    Descriptor += EXTERNAL1_INT;
/*
  if (INTCON3bits.INT2IE)
    Descriptor += EXTERNAL2_INT;
*/
  if (PIE1bits.RCIE)
    Descriptor += SERIAL_RC_INT;	

  if (PIE1bits.TXIE)
    Descriptor += SERIAL_RC_INT;	

  INTCONbits.GIE = 1;
  return (E_OK);
}

/**********************************************************************
*                                                                     
*       EnableAllInterrupt                                            
*                                                                     
**********************************************************************/
StatusType EnableAllInterrupts(void)
{
  INTCONbits.GIE = 1;
  return (E_OK);
}

/**********************************************************************
*                                                                     
*       DisableAllInterrupt                                           
*                                                                    
**********************************************************************/
StatusType DisableAllInterrupts(void)
{
  INTCONbits.GIE = 0;
  return (E_OK);
}
