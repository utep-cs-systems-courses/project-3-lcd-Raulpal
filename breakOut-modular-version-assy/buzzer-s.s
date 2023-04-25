	.arch msp430g2553
	.p2align 2
	.text

	.equ BIT6, 64		; BIT6 = 64
	.equ BIT7, 128		; BIT7 = 128
        .equ SOUND, 192		; BIT6 | BIT7
	
	.global buzzer_init
	.global buzzer_set_period
	
	.extern timerAUpmode
	.extern P2SEL2
	.extern P2SEL
	.extern P2DIR

	.extern CCR0
	.extern CCR1

		
buzzer_init:
	
	call #timerAUpmode

	bic #SOUND, &P2SEL2	;P2SEL2 &= ~SOUND
	
	bic #BIT7, &P2SEL	;P2SEL &= ~BIT7
	
	bis #BIT6, &P2SEL	;P2SEL |= BIT6

	mov #BIT6, &P2DIR	; P2DIR = BIT6
	pop r0
	
buzzer_set_period:

	mov r12, &CCR0		;CCR0 = cycles
	rrc r12			; cycles >>1
	mov r12, &CCR1		;
	pop r0
	

	
