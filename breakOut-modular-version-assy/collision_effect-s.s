	.arch msp430g2553
	.p2align 2
	.text


	.global sound_effect
	
	.extern buzzer_set_period

	

sound_effect:

	mov #5000, r12		;r12 = 5000
	call #buzzer_set_period	; function call
	
	mov #40000, r12
	jmp delay
	pop r0
delay:
	dec r12
	jnz delay
	
	mov #0, r12
	call #buzzer_set_period	; function call

	pop r0
