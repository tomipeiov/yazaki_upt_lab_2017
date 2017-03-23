;/**********************************************************************/
;/*                                                                    */
;/* File name: kernel.asm                                              */
;/*                                                                    */
;/* Since:     2002/09/09                                              */
;/*                                                                    */
;/* Version:   1.11                                                    */
;/*                                                                    */
;/* Author:    MONTAGNE Xavier [XM] {link xavier.montagne@wanadoo.fr}  */
;/*                                                                    */
;/* Purpose:   Kernel core code.                                       */
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
;/*   2002/11/11  [XM] Because kernel and services are not.            */
;/*                    interruptible, add calls to CGI & SGI macros.   */
;/*   2003/01/10  [XM] Remove the LIST directive.                      */
;/*                    Remove the #include directive.                  */
;/*   2003/01/26  [XM] Replace fixed SECTIONS by relocatable SECTIONS. */
;/*   2003/02/02  [XM] Modify the call_from update (add BSR selection).*/
;/*   2003/02/12  [XM] Modify idle, _save_ctx and task jumping code    */
;/*                    to allow services call from ISR.                */
;/*   2003/05/10  [XM] Added STATUS_save and BSR_save variables.       */
;/*   2003/08/03  [XM] Added "device.inc" include.                     */
;/*                                                                    */
;/**********************************************************************/


	#include "device.inc"

;/**********************************************************************
; * Kernel RAM area.
; **********************************************************************/
KERNEL_RAM    UDATA
id_tsk_run    RES     1                       ; ID of the current task
temp          RES     1
id            RES     1
stack_size    RES     1
temp2         RES     1
permut        RES     1
call_from     RES     1                       ; 0x 0 0 0 0 0 INT Kernel Task

STATUS_save   RES     1
BSR_save      RES     1

;/**********************************************************************
; * Share global variables with other sections.
; **********************************************************************/
	GLOBAL 		call_from
	GLOBAL		id_tsk_run
	GLOBAL		STATUS_save
	GLOBAL      BSR_save	

;/**********************************************************************
; * Shared variables defined in other section.
; **********************************************************************/
	extern tsk_1_stack
	extern tsk_2_stack
	extern tsk_3_stack
	extern tsk_4_stack
	extern tsk_5_stack
	extern tsk_6_stack
	extern tsk_7_stack
	extern tsk_8_stack
	extern tsk_1_state
	extern tsk_2_state
	extern tsk_3_state
	extern tsk_4_state
	extern tsk_5_state
	extern tsk_6_state
	extern tsk_7_state
	extern tsk_8_state

;/**********************************************************************
; * Hook routines activated by the -D compiler option.
; **********************************************************************/
#IFDEF STARTUPHOOK
	extern StartupHook
#ENDIF

#IFDEF PRETASKHOOK
	extern PreTaskHook
#ENDIF

#IFDEF POSTTASKHOOK
	extern PostTaskHook
#ENDIF


;/**********************************************************************
; * ------------------------- KERNEL INIT ------------------------------
; *
; * Here is the init phase of the kernel, it means the main access to 
; * the kernel after StartOS call.
; *
; **********************************************************************/
KERNEL_ROM	CODE
_kernel		
		GLOBAL 	_kernel                           ; Beginning of kernel code
		clrf    FSR0H
		clrf    FSR0L
		clrf    FSR1L
		clrf    FSR1H
		clrf    TBLPTRU
		clrf    PCLATH
		movlw   0xAF
		
_k_init_RAM	                                      ; Clear the first RAM bank
		clrf    POSTINC0
		cpfseq  FSR0L
		bra     _k_init_RAM

		clrf    FSR0H
		clrf    FSR0L
		clrf    STKPTR
		movlw   0x1E
		
_k_init_STK                                       ; Clear the hardware stack
		incf    STKPTR
		clrf    TOSU
		clrf    TOSH
		clrf    TOSL
		cpfseq  STKPTR
		bra     _k_init_STK
		clrf    STKPTR
		incf    STKPTR

		movlw   0xc5                              ; Prescaler timer0 = 1/8
		movwf   T0CON
		clrf    INTCON1
		clrf    INTCON2
		clrf    PIE1
		clrf    PIE2
		clrf    INTCON
		bsf     INTCON, 5
		bsf	    INTCON, 6

		clrf    TMR0L
		clrf    TMR0H

		bra     _parser


;/**********************************************************************
; * ----------------------- KERNEL TASK PARSER -------------------------
; *
; * Here is the init phase of the kernel, it means the main access to 
; * the kernel after StartOS call.
; *
; **********************************************************************/
_parser
        movlb   0
		clrf    STKPTR                            ; Init
		incf	STKPTR
		clrf	temp
		clrf	permut
		incf	permut
		clrf	FSR0H                             ; 
		movlw	tsk_1_stack                       ; tsk_1_stack is pointed by FSR0
		movwf	FSR0L                             ;

		movlw   0x00                              ; The Task Descriptor is
		movwf   TBLPTRU                           ; located at the adress 
		movwf   TBLPTRH                           ; 0x000050
		movlw   0x50
		movwf   TBLPTRL

; /* --------- TASKDESC.C CONTENT PARSING ---------- */
_parser_init
		TBLRD   *+                                ; First access the priority
		movf    TABLAT, w                         ; and parse upto the end
		btfsc   STATUS, Z                         ; (priority = 0)
		bra	    _parser_update

		movff   TABLAT, INDF0                     ; Store the priority into
		swapf   INDF0                             ; RAM_DESC task area
		rlncf   INDF0                             ;
		TBLRD   *+                                ; Store the stack size
		movf    TABLAT, w
		movwf   stack_size
		TBLRD   *+                                 ; Store low stack adr in TOSL
		movf    TABLAT, w	
		movwf   TOSL
		TBLRD   *+                                ; Store middle stack adr in TOSH
		movf    TABLAT, w
		movwf   TOSH
		movlw   0                                 ; Store 0 in TOSU
		movwf   TOSU
		movf    STKPTR, w                         ; Store Stack pointer adr in
		addwf   INDF0, 1                          ; RAM_DESC task area
		movf    stack_size, w                      
		addwf   STKPTR, 1                         ; Shift STRPTR for next process
		TBLRD   *+                                ; Store the initial state
		bsf     FSR0L, 3                          ; Shift to high RAM_DESC area
		movf    TABLAT, w
		addwf   INDF0, 1
		TBLRD   *+                                ; Store the task ID
		swapf   TABLAT
		movf    TABLAT, w
		addwf   INDF0, 1
		bcf	    FSR0L, 3                          ; Shift to low RAM_DESC area
		incf    FSR0L
		TBLRD   *+                                ; Don't care the context adress
		TBLRD   *+ 
		bra     _parser_init                      ; while another task exists


; /* ----- REARRANGE TASK ORDER FCT TO PRIORITY ---- */
_parser_update
		movlw   tsk_1_stack
		movwf   FSR0L
		movf    permut, w                         ; update finished ?
		btfsc   STATUS, Z
		bra     _isHook                           ; for STARTUPHOOK only
		clrf    permut

_parser_update_loop	
		movlw   0xF0                              ; 
		andwf   INDF0, w
		movwf   temp                              ; store the priority of a task
		movff   INDF0, temp2                      ; store prio + ID of the task
		movlw   0xF0
		andwf   PREINC0, w                        ; compare with the next task
		cpfseq  temp
		bra     _parser_update_diff               ; task swapping if necessary
		bra	    _parser_update_rr                 ; if equal => round robin

_parser_update_diff
		cpfslt  temp
		bra     _parser_update_swap               ; task swapping
		cpfsgt  temp
		bra	    _parser_update_loop	              ; nothing to do 

_parser_update_rr
		bsf     FSR0L, 3
		decf    FSR0L
		bsf	    INDF0, 3                          ; task scheduled
		incf    FSR0L
		bsf     INDF0, 3                          ; task scheduled
		bcf     FSR0L, 3
		bra     _parser_update_loop

_parser_update_swap
		movf    INDF0, w                          ; the priority last task is 0
		btfsc   STATUS, Z                         ; is swap finished ?
		bra     _parser_update

		decf    FSR0L                             ; WREG = higher priority task
		movwf   INDF0
		incf    FSR0L
		movff   temp2, INDF0                      ; temp2 = lowest priority task

		bsf     FSR0L, 3                          ; swap the low part of the 
		movff   INDF0, temp2                      ; RAM_DESC task area
		decf    FSR0L
		movf    INDF0, w
		movff   temp2, INDF0
		incf    FSR0L
		movwf   INDF0
		bcf     FSR0L, 3
		incf    permut
		bra     _parser_update	
		
_isHook                                          ; Hook kernel service routine
	#IFDEF	STARTUPHOOK
		call    StartupHook
	#ENDIF
		bra     _sched


;/**********************************************************************
; * --------------------- KERNEL TASK SCHEDULER ------------------------
; *
; * The scheduler manage the task switching during application running.
; *
; **********************************************************************/
_sched
		GLOBAL  _sched
	#IFDEF POSTTASKHOOK
		call    PostTaskHook
	#ENDIF
		clrf    FSR0H
		movlw   tsk_1_state-1
		movwf   FSR0L
	
_sched_clr_run
		incf    FSR0L                             ; tsk_1_state pointed by FSR0
		movlw   tsk_8_state+1
		subwf   FSR0L, w
		bz      _sched_clr_end                    ; if all RUNNING bits cleared
		btfss   INDF0, 1                          ; skip if task is running 
		bra     _sched_clr_run                    ; running task is not found
		bcf     INDF0, 1                          ; task is no more running
		 
_sched_clr_end
		clrf    id_tsk_run                        ; no more task in running state
		movlw   tsk_1_state-1
		movwf   FSR0L
			
_sched_exec_tsk
		incf    FSR0L
		btfss   INDF0, 0                          ; skip if task READY
		bra     _sched_jmp_next	   
		btfsc   INDF0, 2                          ; skip if task not STOPPED
		bra     _sched_jmp_next
		
		movlb   0
		bsf     INDF0, 1                          ; task is RUNNING now !
		movlw   0xF0                              ; save ID task in id_tsk_running
		andwf   INDF0, w
		movwf   id_tsk_run
		swapf   id_tsk_run	

	#IFDEF	PRETASKHOOK                           ; Hook kernel service routine
		call    PreTaskHook
	#ENDIF

		bcf     FSR0L, 3                          ; Look up low RAM_DESC task
		movlw   0x1F                              ; load stack adr from task desc
		andwf   INDF0, w
		movwf   STKPTR                            ; set stack adr in STRPTR

		movlw   0x00                              ; ROM_DESC at 0x000050
		movwf   TBLPTRU
		movwf   TBLPTRH
		movlw   0x55
		movwf   TBLPTRL

;/**********************************************************************
; * ------------------------- RESTORE CONTEXT --------------------------
; *
; * Copy the content of the context (task ram area) into Special File 
; * Registers.
; *
; **********************************************************************/
restore_ctx	
		movf    id_tsk_run, w
		TBLRD   *+                                ; find the task id from ROM_DESC
		cpfseq  TABLAT
		bra     restore_next
		bra     restore_adr
		
restore_next
		movlw   7
		addwf   TBLPTRL, 1                        ; Next task located at @+7 bytes 
		bra     restore_ctx

restore_adr	
		TBLRD   *+                                ; access to the ctx adress
		movff   TABLAT, FSR0L
		TBLRD   *+
		movff   TABLAT, FSR0H

; /* ----------- RESTORE THE STACK BUFFER ----------- */
restore_stack	
		movlw   0x0B
		addwf   FSR0L
		movlw   0x00
		addwfc  FSR0H
		clrf    FSR1L
		clrf    FSR1H
		movlw   STACK_SIZE                        ; STACK_SIZE

restore_stack_next
		movff   POSTINC0, POSTINC1                ; Copy task ram area dedicated
		decf    WREG                              ; STACK_SIZE
		bnz     restore_stack_next
		
		TBLRD   *-
		TBLRD   *-
		TBLRD   *+
		movff   TABLAT, FSR0L
		TBLRD   *
		movff   TABLAT, FSR0H

		movlw   0x0B                              ; we start to restore SFR
		addwf   FSR0L	
		movlw   0x00
		addwfc  FSR0H	  
		decf    FSR0L
		movff   POSTDEC0, PRODL
		movff   POSTDEC0, PRODH
		movff   POSTDEC0, FSR2L
		movff   POSTDEC0, FSR2H
		movff   POSTDEC0, FSR1L
		movff   POSTDEC0, FSR1H
		movff   POSTDEC0, temp
		movff   POSTDEC0, temp2
		movff   POSTDEC0, permut
		movff   POSTDEC0, BSR
		movff   INDF0, id

		movff   temp, FSR0L
		movff   temp2, FSR0H
		movff   id, WREG
		movff   permut, STATUS
		
		movff   BSR, temp
		
		movlb   0
		bcf     call_from, 1, 1
		bcf     call_from, 0, 1
		movff   temp, BSR
		movff   id, WREG		

		retfie                                    ; JUMP TO THE NEXT RUNNING TASK !!!


_sched_clr_next
		movlw	0xFF                              ; Limite de RAM_DESC
		subwf	FSR0L, w
		bnz		_sched_clr_run 
		movlw	tsk_1_state-1 
		movwf	FSR0L
		bra		_sched_clr_run

_sched_jmp_next
		movlw	tsk_8_state                       ; Look up the next task up to the end
		subwf	FSR0L, w
		bnz		_sched_exec_tsk
				
		movlb	0
		bcf     call_from, 1, 1
		bsf 	call_from, 0, 1
		bsf		INTCON, 7                         ; General Interrupt Enable ON
		
_while
		bsf 	call_from, 0, 1
		bra		_while                            ; No task in RUNNING state


;/**********************************************************************
; * ----------------- SCHEDULER FOR ROUND ROBIN ONLY -------------------
; *
; * Futur use : round robin algorithm in case of tasks with same priority.
; * Not mandatory by OSEK standard.
; *
; **********************************************************************/
_scheduler	
		GLOBAL	_scheduler
		bcf		INTCON, 5                         ; Disable the Timer0 INT
		bcf		INTCON, 2
		bcf		INTCON, 7
		clrf	FSR0H                             ; tsk_1_state pointed by FSR0
		movlw	tsk_1_state-1
		movwf	FSR0L

_scheduler_jmp
		incf	FSR0L
		movf	INDF0, w 	  
		btfss	INDF0, 3                          ; skip if task scheduled
		bra 	_scheduler_next
		btfss	INDF0, 1                          ; skip if task is running
		bra		_scheduler_next
		movwf	temp                              ; tsk Sch in temp
		bcf		FSR0L, 3
		movf	INDF0, w
		movwf	temp2                             ; tsk_desc in temp2
		bsf		FSR0L, 3

_scheduler_lp	
		incf	FSR0L
		movf	INDF0, w
		btfss	INDF0, 3                          ; skip if task is scheduled
		bra 	_scheduler_ordo
		decf	FSR0L                             ; shift the other sch task
		movwf	INDF0
		incf	FSR0L
		bcf		FSR0L, 3                          ; shift the other sch_desc task
		movf	INDF0, w
		decf	FSR0L
		movwf	INDF0
		incf	FSR0L
		bsf		FSR0L, 3
		bra 	_scheduler_lp

_scheduler_ordo	
		decf	FSR0L
		movf	temp, w
		movwf	INDF0
		bcf		FSR0L, 3
		movf	temp2, w
		movwf	INDF0

		clrf	TMR0L 
		bsf		INTCON, 5                          ; Enable the TImer0 INT
		bcf		INTCON, 2
		bsf		INTCON, 7
		bra		_sched

_scheduler_next
		movlw	tsk_1_state
		subwf	FSR0L, w
		bnz		_scheduler_jmp
		movlw	tsk_1_state-1
		movwf	FSR0L
		bra		_scheduler_jmp

;/**********************************************************************
; * ----------------------- FOR BASIC TASK ONLY ------------------------
; *
; * After terminating a task, we loose the start adress of the task, 
; * first located in the first place
; * of the stack.
; *
; **********************************************************************/
_restore_start_adr
		GLOBAL	_restore_start_adr
		movlw	0x00                              ; ROM_DESC en 0x000050
		movwf	TBLPTRU
		movwf	TBLPTRH
		movlw	0x55                              ; offset 5 for start adress
		movwf	TBLPTRL
		
		movlb   0

_restore_find	
		movf	id_tsk_run, w                     ; look for the task area in ROM_DESC
		TBLRD 	*-                               
		cpfseq	TABLAT 
		bra 	_restore_next                     ; continu to search
		bra 	_restore_read                     ; task ID found
		
_restore_next	
		movlw	9                                 ; offset 9 for next task ID
		addwf	TBLPTRL, 1
		bra		_restore_find

_restore_read	
		TBLRD	*-                                ; Access to the start adress		  
		TBLRD	*-	
		clrf	TOSU
		movf	TABLAT, w
		movwf	TOSH
		TBLRD	*+
		movf	TABLAT, w
		movwf	TOSL                              ; Set the value into STKPTR
		goto	_sched                            ; Determine the next RUNNING task


;/**********************************************************************
; * -------------------------- STORE CONTEXT ---------------------------
; *
; * Copy the content of Special File Registers into the context 
; * (task ram area).
; *
; **********************************************************************/
_save_ctx
		GLOBAL	_save_ctx
		
		movlb	0		
		btfss	call_from, 1                      ; skip if call from task level
		return
		btfsc   call_from, 0
		return

		movff	WREG, id                          ; 
		movff	FSR0H, temp2                      ; but id is really the ID of task
		movff	FSR0L, temp

		clrf	BSR
		clrf	WREG                              ; immediat return if
		cpfsgt	id_tsk_run, 1                     ; no task in READY state
		return

		movlw	0x00                              ; ROM_DESC at 0x000050
		movwf	TBLPTRU
		movwf	TBLPTRH
		movlw	0x55                              ; offset 5 for start adress
		movwf	TBLPTRL
		
store_ctx	
		movf	id_tsk_run, w, 1
		TBLRD 	*+                                ; find the task id
		cpfseq	TABLAT
		bra		store_next                        ; continu to search
		bra 	store_adr                         ; task ID found
		
store_next	
		movlw	7                                 ; offset 7 for next task ID
		addwf	TBLPTRL, 1
		bra		store_ctx

store_adr	
		TBLRD	*+                                ; access the context adr
		movff	TABLAT, FSR0L;
		TBLRD	*+ 
		movff	TABLAT, FSR0H;
		
		movlw	0x0B                              ; we start to store SFR
		addwf	FSR0L	
		movlw	0x00
		addwfc  FSR0H	  
		decf	FSR0L          
		movff	PRODL, POSTDEC0                   ; PRODL
		movff	PRODH, POSTDEC0                   ; PRODH
		movff	FSR2L, POSTDEC0                   ; FSR2L
		movff	FSR2H, POSTDEC0                   ; FSR2H
		movff	FSR1L, POSTDEC0                   ; FSR1L
		movff	FSR1H, POSTDEC0                   ; FSR1H
		movff	temp,  POSTDEC0                   ; FSR0L
		movff	temp2, POSTDEC0                   ; FSR0H
		movff	STATUS_save,POSTDEC0              ; STATUS
		movff	BSR_save, POSTDEC0                ; BSR
		movff	id, INDF0                         ; WREG

;/**********************************************************************
; * -------------------------- STACK STORAGE ---------------------------
; *
; * Set the content of the stack just after the CTX SAVE area of the task.
; *
; **********************************************************************/
store_stack	
		movlw	0x0B                              ; Lenght of the ctx structure
		addwf	FSR0L
		movlw	0x00
		addwfc	FSR0H
		clrf	FSR1L                             ; Software stack pointed by FSR1
		clrf	FSR1H
		movlw	STACK_SIZE                        ; STACK_SIZE

store_stack_next	
		movff	POSTINC1, POSTINC0                ; Store software stack after ctx area
		decf	WREG
		bnz		store_stack_next

		return

		END                                       ; Directive 'end of program'



		
