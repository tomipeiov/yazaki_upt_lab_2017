;/**********************************************************************/
;/*                                                                    */
;/* File name: int.asm                                                 */
;/*                                                                    */
;/* Since:     2002/09/09                                              */
;/*                                                                    */
;/* Version:   1.11                                                    */
;/*                                                                    */
;/* Author:    MONTAGNE Xavier [XM] {link xavier.montagne@wanadoo.fr}  */
;/*                                                                    */
;/* Purpose:   Definition of the interrupt vector table.               */
;/*                                                                    */
;/* Distribution: This file is part of PICOS18                         */
;/*               PICOS18 is free software; you can redistribute it    */
;/*               and/or modify it under the terms of the GNU General  */
;/*               Public License as published by the Free Software     */
;/*               Foundation; either version 2, or (at your option)    */
;/*               any later version.                                   */
;/*                                                                    */
;/*               PICOS18 is distributed in the hope that it will be   */
;/*               useful, but WITHOUT ANY WARRANTY; without even the   */
;/*               implied warranty of MERCHANTABILITY or FITNESS FOR A */
;/*               PARTICULAR PURPOSE.  See the GNU General Public      */
;/*               License for more details.                            */
;/*                                                                    */
;/*               You should have received a copy of the GNU General   */
;/*               Public License along with gpsim; see the file        */
;/*               COPYING.txt. If not, write to the Free Software      */
;/*               Foundation, 59 Temple Place - Suite 330,             */
;/*               Boston, MA 02111-1307, USA.                          */
;/*                                                                    */
;/* History:                                                           */
;/*   2002/09/09  [XM] Create this file.                               */
;/*   2003/01/10  [XM] Remove the LIST directive.                      */
;/*                    Replace the #include directive (kernel.h).      */
;/*   2003/01/26  [XM] Replace fixed SECTIONS by relocatable SECTIONS. */
;/*   2003/08/03  [XM] Added "device.inc" include.                     */
;/*                                                                    */
;/**********************************************************************/

        #include "device.inc"

;/**********************************************************************
; * Shared symbols defined in other section.
; **********************************************************************/
        EXTERN 	_scheduler
        EXTERN  AddOneTick

;/**********************************************************************
; * TIMER0 interrupt vector table.
; **********************************************************************/
INT		CODE                                 ; interrupt vector location
        goto 	 AddOneTick

        END
