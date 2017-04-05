/**********************************************************************/
/*                                                                    */
/* File name: taskdesc.c                                              */
/*                                                                    */
/* Since:     2002/09/09                                              */
/*                                                                    */
/* Version:   1.11                                                    */
/*                                                                    */
/* Author:    MONTAGNE Xavier [XM] {link xavier.montagne@wanadoo.fr}  */
/*                                                                    */
/* Purpose:   Kind of OIL file where all the features of the tasks    */
/*            are described.                                          */
/*                                                                    */
/*           rom_desc_tsk foo = {                                     */
/*               0x..,    Priority level [0:7],0 the most significant */
/*               0x..,    Stack depth, nb of adress storable in stack */
/*               0x....,  Start adress of the task                    */
/*               0x..,    Task state at start [RUN/WAIT/READY/SUSPEND]*/
/*               0x..,    Identification number of the task           */
/*               0x....   Context adress (adress of the task RAM area)*/
/*               };                                                   */
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
/*   2002/10/27  [XM] Create this file                                */
/*   2003/01/26  [XM] Replace fixed SECTIONS by relocatable SECTIONS. */
/*   2003/02/02  [XM] Linker solves tha data & code address symbols.  */
/*                    Use of DeclareTask & DeclareRAM macros.         */
/*   2003/08/03  [XM] Added "device.h" include.                       */
/*                    Use now the ID of the task defined in task.h.   */
/*                                                                    */
/**********************************************************************/

#include "device.h"
#include "pro_man.h"
#include "task.h"

/**********************************************************************
 * ------------------ DATA - CODE SYMBOLS DEFINITION ------------------
 **********************************************************************/
DeclareTask(Led_ON);
DeclareTask(YZK_lab);


DeclareRAM(ctx_led_on);
DeclareRAM(ctx_Yzk_lab);


/**********************************************************************
 * ---------------------- TASK DESCRIPTOR SECTION ---------------------
 **********************************************************************/
#pragma		romdata		DESC_ROM

/**********************************************************************
 * --------------------------- Led_ON task ----------------------------
 **********************************************************************/
rom_desc_tsk rom_desc_led_ON = {
	0x04,                              /* prioinit from 0 to 7        */
	0x04,                              /* stacksize in word [32 bits] */
	Led_ON,                            /* adr_tsk in 16 bits          */
	0x01,                              /* state at init phase         */
	LED_ON,                            /* id_tsk from 1 to 8          */
	&ctx_led_on                        /* ctx_tsk in 16 bits          */
};

rom_desc_tsk rom_desc_YZK_LAB = {
	0x04,                              /* prioinit from 0 to 7        */
	0x04,                              /* stacksize in word [32 bits] */
	YZK_lab,                            /* adr_tsk in 16 bits          */
	0x00,                              /* state at init phase         */
	YZK_TASK_NAME,                            /* id_tsk from 1 to 8          */
	&ctx_Yzk_lab                        /* ctx_tsk in 16 bits          */
};

/**********************************************************************
 * --------------------- END TASK DESCRIPTOR SECTION ------------------
 **********************************************************************/
rom_desc_tsk end = {
	0x00,                              /* prioinit from 0 to 7        */
	0x00,                              /* stacksize in word [32 bits] */
	0x0000,                            /* adr_tsk in 16 bits          */
	0x00,                              /* state at init phase         */
	0x00,                              /* id_tsk from 1 to 8          */
	0x0000                             /* ctx_tsk in 16 bits          */
};

	

