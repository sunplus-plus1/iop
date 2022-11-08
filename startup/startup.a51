$NOMOD51
/*****************************************************************************
  Copyright (c) 1999-2002  Digital Core Design  DCD
******************************************************************************
  Please review the terms of the license agreement before using this file.
  If you are not an authorized user, please destroy this source code file
  and notify DCD immediately that you inadvertently received an unauthorized
  copy.
******************************************************************************
------------------------------------------------------------------------------
 Project name         : DoCD
 Project description  : DoCD board demo

 File name            : strtup.a51
 File contents        : DoCD strtup operation
------------------------------------------------------------------------------
 Design Engineer      : T.K.
 Version              : 1.00
 Last modification    : 2002-10-09
----------------------------------------------------------------------------*/
IDATALEN	EQU	256	; the length of IDATA memory in bytes.
;IDATALEN	EQU	0	; the length of IDATA memory in bytes.

STRETCH_VAL     EQU     1       ; STRETCH values range 1 to 8. Defines
                                ; XRAMRD, XRAMWR pulses witdth in clock periods
WDTIMEOUT_VAL   EQU     0       ; Watchdog timeout interval 0,1,2,3
                                ; 0 = 2^17; 1 = 2^20; 2 = 2^23; 3 = 2^26
;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
;
;XDATASTART	EQU	0F000H	; the absolute start-address of XDATA memory
;XDATALEN	EQU	01000H	; the length of XDATA memory in bytes.
                                ; up to 16 MB
;Leon add
XDATASTART	EQU	00000H	; the absolute start-address of XDATA memory
XDATALEN	EQU	08000H	; the length of XDATA memory in bytes.
                                ; up to 16 MB

;
PDATASTART	EQU	0H	; the absolute start-address of PDATA memory
PDATALEN	EQU	0H	; the length of PDATA memory in bytes.


;
;  Notes:  The IDATA space overlaps physically the DATA and BIT areas of the
;          8051 CPU. At minimum the memory space occupied from the C51
;          run-time routines must be set to zero.
;------------------------------------------------------------------------------
;
;  Reentrant Stack Initilization
;
;  The following EQU statements define the stack pointer for reentrant
;  functions and initialized it:
;
;  Stack Space for reentrant functions in the SMALL model.
;IBPSTACK	EQU	0	; set to 1 if small reentrant is used.
;IBPSTACKTOP	EQU	0FH+1	; set top of stack to highest location+1.
;;Leon add
IBPSTACK	EQU	0	; set to 1 if small reentrant is used.
IBPSTACKTOP	EQU	8FH+1	; set top of stack to highest location+1.
;
;  Stack Space for reentrant functions in the LARGE model.
;XBPSTACK	EQU	0	; set to 1 if large reentrant is used.
;XBPSTACKTOP	EQU	0FH+1; set top of stack to highest location+1.
;;Leon add
XBPSTACK	EQU	1	; set to 1 if large reentrant is used.
XBPSTACKTOP	EQU	 03FFH+1; set top of stack to highest location+1.
;
;  Stack Space for reentrant functions in the COMPACT model.
;PBPSTACK	EQU	0	; set to 1 if compact reentrant is used.
;PBPSTACKTOP	EQU	0FH+1; set top of stack to highest location+1.
;;Leon
PBPSTACK	EQU	0	; set to 1 if compact reentrant is used.
PBPSTACKTOP	EQU	8FH+1; set top of stack to highest location+1.
;
;------------------------------------------------------------------------------
;
;  Page Definition for Using the Compact Model with 64 KByte xdata RAM
;
;  The following EQU statements define the xdata page used for pdata
;  variables. The EQU PPAGE must conform with the PPAGE control used
;  in the linker invocation.
;
;PPAGEENABLE	EQU	0	; set to 1 if pdata object are used.
;PPAGE		EQU	0	; define PPAGE number.
;;Leon added
PPAGEENABLE	EQU	0	; set to 1 if pdata object are used.
PPAGE		EQU	0	; define PPAGE number.

;
;------------------------------------------------------------------------------
;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "dp8051xp.h"
;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		NAME	?C_STARTUP


?C_C51STARTUP	SEGMENT   CODE
;;Leon
;;?STACK		SEGMENT   IDATA
;;
;;		RSEG	?STACK
;;		DS	1

;;Leon add
ISEG    AT      0x90
?STACK: DS      0x100 - ?STACK
;;Leon add
;;ISEG    AT      0xB0
;;?STACK: DS      0x100 - ?STACK


		EXTRN CODE (?C_START)
		PUBLIC	?C_STARTUP

		CSEG	AT	0
?C_STARTUP:	LJMP	STARTUP1
;?C_STARTUP:	LJMP	SKIP_L
		RSEG	?C_C51STARTUP

		;Leon add
		EXTRN CODE (ex0_isr)
		CSEG    AT  03H         ; 03H is address for external interrupt0
		LJMP ex0_isr


		EXTRN CODE (timer0_isr)
		CSEG    AT  0BH         ; 0BH is address for timer0 interrupt1
		LJMP timer0_isr

		EXTRN CODE (timer1_isr)
		CSEG    AT  1BH         ; 0BH is address for timer0 interrupt1
		LJMP timer1_isr


		;Leon add





STARTUP1:
;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
;                MOV CKCON,#(WDTIMEOUT_VAL*64 + (STRETCH_VAL -1))  ; Added by DCD
;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
;IF IDATALEN <> 0
;		MOV	R0,#IDATALEN - 1
;		CLR	A
;IDATALOOP:	MOV	@R0,A
;		DJNZ	R0,IDATALOOP
;ENDIF

;IF XDATALEN <> 0
;		MOV	DPTR,#XDATASTART
;		MOV	R7,#LOW (XDATALEN)
;  IF (LOW (XDATALEN)) <> 0
;		MOV	R6,#(HIGH (XDATALEN)) +1
;  ELSE
;		MOV	R6,#HIGH (XDATALEN)
;  ENDIF
;		CLR	A
;XDATALOOP:	MOVX	@DPTR,A
;		INC	DPTR
;		DJNZ	R7,XDATALOOP
;		DJNZ	R6,XDATALOOP
;ENDIF

IF PPAGEENABLE <> 0
		MOV	P2,#PPAGE
ENDIF

IF PDATALEN <> 0
		MOV	R0,#PDATASTART
		MOV	R7,#LOW (PDATALEN)
		CLR	A
PDATALOOP:	MOVX	@R0,A
		INC	R0
		DJNZ	R7,PDATALOOP
ENDIF

IF IBPSTACK <> 0
EXTRN DATA (?C_IBP)

		MOV	?C_IBP,#LOW IBPSTACKTOP
ENDIF


IF XBPSTACK <> 0
EXTRN DATA (?C_XBP)

		MOV	?C_XBP,#HIGH XBPSTACKTOP
		MOV	?C_XBP+1,#LOW XBPSTACKTOP



ENDIF

IF PBPSTACK <> 0
EXTRN DATA (?C_PBP)
		MOV	?C_PBP,#LOW PBPSTACKTOP
ENDIF
SKIP_L:
		MOV	SP,#?STACK-1
; This code is required if you use L51_BANK.A51 with Banking Mode 4
; EXTRN CODE (?B_SWITCH0)
;               CALL    ?B_SWITCH0      ; init bank mechanism to code bank 0
		LJMP	?C_START
		END
