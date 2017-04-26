;/**********************************************************************/
;/*                                                                    */
;/* File name: device.inc                                              */
;/*                                                                    */
;/* Since:     2003/08/03                                              */
;/*                                                                    */
;/* Version:   1.11                                                    */
;/*                                                                    */
;/* Author:    MONTAGNE Xavier [XM] {link xavier.montagne@wanadoo.fr}  */
;/*            DEVINE Dan      [DD]                                    */
;/*                                                                    */
;/* Purpose:   Specify the PIC device header file.                     */
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
;/*   2003/08/03  [XM] Original idea of DD.                            */
;/*                                                                    */
;/**********************************************************************/

#ifndef _DEVICE_INC
#define _DEVICE_INC

#include <p18f452.inc>         ; processor specific variable definitions


;/* Please add here anything related to the specific target :          */

;/* Should be equal to .tempdata + MATH_DATA size (from map file)      */
#define STACK_SIZE             0x10

#endif ;/* _DEVICE_INC */
