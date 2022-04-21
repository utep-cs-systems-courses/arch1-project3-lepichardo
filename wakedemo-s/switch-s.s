	;;
	.extern msp430.h
	.extern libTimer.h
	.extern lcdutils.h
	.extern lcddraw.h
	.extern switch.h

	.text
	.global switch_interrupt_handler
	
switch_interrupt_handler:
	sub #2, 0(r1) 		; space for local p2val
	call #switch_update_interrupt_sense
	;; p2val in r12
	xor.b #0xff, r12
	and.b #0x1f, r12
	mov.b r12, &switches
	add #2, 0(r1)
	pop r0

