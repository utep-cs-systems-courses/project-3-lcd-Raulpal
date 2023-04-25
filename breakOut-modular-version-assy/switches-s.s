	.arch msp430g2553
	.p2align 2		
	.text

	.equ SW1, 1
	.equ SW4, 8
	.equ SWITCHES, 9
	
	.global switch_update_interrupt_sense
	.global switch_init
	.global switch_interrupt_handler

	.extern P2OUT
	.extern P2DIR
	.extern P2IE
	.extern P2REN
	.extern P2IES
	.extern P2IN

	.data
	.global switches
         switches:.word 0

	.text

	
switch_update_interrupt_sense:
	sub #2, r1		; move stack pointer down
	mov &P2IN, 0(r1) 	;p2val

	mov 0(r1), r12		; r12= p2val
	and #SWITCHES, r12	; r12 &= SWITCHES

	bis r12, &P2IES		;&p2ies |= r12

	mov 0(r1), r12		;r12 = p2val
	bis #~SWITCHES, r12	;r12 |= ~SWITCHES	

	and r12, &P2IES		;&p2ies &= r12
	mov 0(r1), r12  	;p2val in first parameter

	add #2, r1		;change stack pointer back 
	pop r0			;return 

switch_init:
	
	bis #SWITCHES, &P2REN	;P2REN |= SWITCHES
	bis #SWITCHES, &P2IE	; P2IE |= SWITCHES
	bis #SWITCHES, &P2OUT	; P2OUT |= SWITCHES
	and #~SWITCHES, &P2DIR	;P2DIR &= ~SWITCHES
	call #switch_update_interrupt_sense ; function call
	pop r0				    ;return

switch_interrupt_handler:
	call #switch_update_interrupt_sense ;function cll p2val stored in r12
	mov #SWITCHES, r13		    ;r13 = SWITCHES
	bic r12, r13			    ;r13 &=~r12
	mov r13, &switches		    ;switches = r13
	pop r0				    ;return
