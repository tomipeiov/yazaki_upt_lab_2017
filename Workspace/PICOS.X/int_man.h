/**********************************************************************/
/*                                                                    */
/* File name: int_man.h                                               */
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
/*   2003/01/26  [XM] Replace fixed SECTIONS by relocatable SECTIONS. */
/*                                                                    */
/**********************************************************************/

#ifndef _INT_MAN_h_
#define _INT_MAN_h_

/*****************************************************
 * ----------------- Type definition -----------------
 ****************************************************/
typedef char  IntDescriptorType;
typedef char *IntDescriptorRefType;

/*****************************************************
 * ---------------- Global variables -----------------
 ****************************************************/
extern char call_from;

/*****************************************************
 * -------------------- Defines ----------------------
 ****************************************************/
/* -------------------- Macro --------------------- */
#define ISR(FuncName)       char FuncName(void)
#define EnterISR(void)      call_from = ISR_Category_3;
#define LeaveISR(void)      INTCONbits.GIE = ENABLE;

#define TIMER1_INT          0x01
#define TIMER2_INT          0x02
#define TIMER3_INT          0x04
#define EXTERNAL0_INT       0x08
#define EXTERNAL1_INT       0x10
#define EXTERNAL2_INT       0x20
#define SERIAL_RC_INT       0x40
#define SERIAL_TX_INT       0x80

#define	ISR_Category_3		0x00
#define	ISR_Category_2		0x01

/*
#define GENERAL_INT         0xA1
#define TIMER0_INT          0xA2
#define PORTB_INT           0x06
#define AD_CONV_INT         0x0A
#define SSP_INT             0x0D
#define CCP1_INT            0x0E
#define CCP2_INT            0x0F
#define BUS_COL_INT         0x10
#define LOW_VOLTAGE_INT     0x11
*/

/*****************************************************
 * --------------- From int_man.c file ---------------
 ****************************************************/
StatusType EnableInterrupt(IntDescriptorType Descriptor);
StatusType DisableInterrupt(IntDescriptorType Descriptor);
StatusType GetInterruptDescriptor(IntDescriptorRefType Descriptor);
StatusType EnableAllInterrupts(void);
StatusType DisableAllInterrupts(void);

#endif /* _INT_MAN_h_ */



