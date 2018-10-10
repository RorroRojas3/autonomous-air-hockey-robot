;
; New ExitIsrAndRun Utility  
;
; Author: sippey (sippey@gmail.com)
; Date:   2014/04/10
;
;   This code uses the Reentrant interrupt code in the book as reference
;   "The Definitive Guide to ARM Cortex-M3 and Cortex-M4 Processors" 3rd ed.
;
;   Found from post: http://community.arm.com/thread/4919
;   Downloaded from: http://booksite.elsevier.com/9780124080829/index.php
;   Errta from: http://community.arm.com/docs/DOC-7828  [applied to code]
;  
;

    .cdecls   C,LIST,"reentrance.h"

    .thumb
	.text

    .global ExitIsrAndRun
    .global ExitIsrAndRun_SVC

ExitIsrAndRun
    .if LAZY_STACKING
      ; The following 3 lines are for Cortex-M4 with FPU only
      TST  LR, #0x10 ; Test bit 4, if zero, need to trigger stacking
      IT   EQ
      VMOVEQ.F32  S0, S0  ; Trigger lazy stacking stacking
    .endif

    ; Now we are in Handler mode, using Main Stack, and
    ; SP should be Double word aligned
    
    ; Code in the book say it need xpsr to be saved, but I do not think so
    ;; MRS  R1, xpsr 
    ;; PUSH {R1, LR}       ; Need to save PSR and LR in stack
    PUSH {R0, LR}         ; need align 8

    ; build new stack frame
    SUB  SP, #020h ; Reserve 7 words for dummy stack frame for return
    STR  R0, [SP]   ; store R0 on the created stack
    ADR  R0, ExitIsrAndRun_Stub
    STR  R0, [SP, #24]
    MOV  R0, #01000000h ; New PSR
    STR  R0, [SP, #28]
    
    ;MOV32  R0, #0FFFFFFF9h ; Return to Thread with Main Stack, 8 word stack frame
    EOR  R0, R0
    SUB  R0, #7 ; this way R0=0xFFFFFFF9
    ;MOV  LR, R0
    ;BX   LR
    BX R0       ; should do the same as the previous two in book

    .align 4
ExitIsrAndRun_Stub
    BLX   R0    ; go to the function 
    ; Block SysTick from being triggered just before SVC
    LDR  R0, SysTick_PRI_ADDR ; Address of SysTick priority level
    LDR  R0, [R0]
    MSR  BASEPRI, R0    ; Block SysTick from being triggered
    ISB                 ; Instruction Synchronisation Barrier
 
    SVC   #SVC_CALL_NUMBER ; Use SVC to return to original Thread
    BL    ExitIsrAndRun_Error   ; Use lr to track the error spot

    .align 4
SysTick_PRI_ADDR:
	.word 0xE000ED23 

;-----------------------------------------------------
    .if GEN_SVC_HANDLER
    .align 4
SVC_Handler
    ; Extract SVC number
    TST	    LR,  #0x4	; Test EXC_RETURN bit 2
    ITE     EQ        ; if zero then
    MRSEQ   R0, MSP	  ; Get correct stack pointer to R0
    MRSNE   R0, PSP
    LDR     R1, [R0, #24]  ; Get stacked PC
    LDRB.W  R0, [R1, #-2]  ; Get SVC parameter at stacked PC minus 2
    CMP     R0, #SVC_CALL_NUMBER
    BEQ     ExitIsrAndRun_SVC ; if zero, branch to SVC service 0

    B       SVC_Handler_Other       ; must define this
    BL      ExitIsrAndRun_Error       ; Should not come here
                                      ; Use lr to track the error spot
    .endif
    
    .align 4
ExitIsrAndRun_SVC
    MOVS   R0, #0
    MSR    BASEPRI, R0  ; Enable SysTick again
    ISB    ; Instruction Synchronisation Barrier

    .if LAZY_STACKING
        ; The following 3 lines are for Cortex-M4 with FPU only
        TST  LR, #0x10 ; Test bit 4, if zero, need to trigger stacking
        IT   EQ
        VMOVEQ.F32  S0, S0  ; Trigger lazy stacking stacking
    .endif

    ; Reentrant code finished, we can discard the current stack frame 
    ; and restore the original stack frame. However, the current 
    ; stack frame could be 8 words or 26 words.
    TST     LR,  #0x10	; Test EXC_RETURN bit 4
    ITE     EQ
    ADDEQ   SP, SP, #104 ; LR Bit 4 was 0, 26 words in stack frame
    ADDNE   SP, SP, #32  ; LR Bit 4 was 1,  8 words in stack frame
    POP     {R0, R1}
    ; MSR     xpsr, R0 ; the book say it need xpsr to be saved, but I do not think so
    BX      R1
    
    .align 4
ExitIsrAndRun_Error
    B   ExitIsrAndRun_Error

    .end
