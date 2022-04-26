	;;
	.extern msp430.h
	.extern libTimer.h
	.extern lcdutils.h
	.extern lcddraw.h
	.extern switch.h
	.extern P2IN
	.extern P2IES
	.global switch_interrupt_handler
	.global switch_update_interrupt_sense

	.text
switch_interrupt_handler:
	sub #2, r1 		; space for local p2val
	call #switch_update_interrupt_sense
	;; p2val in r12
	xor.b #0xff, r12
	and.b #0x1f, r12
	mov.b r12, &switches
	add #2, r1
	pop r0


switch_update_interrupt_sense:
	sub #4, r1
	mov.b &P2IN, 0(r1)      ;p2val = P2IN
	mov.b 0(r1), 1(r1)	;t1 = p2val
	mov.b 0(r1), 2(r1)	;t2 = p2val
	and.b #15, 1(r1)	;t1 &= switches where switches is 15 in decimal
	bis.b 1(r1), &P2IES 	;P2IES |= t1 
	bis.b #240, 2(r1)	;t2 |= ~switches
	and.b 2(r1), &P2IES     ;P2IES &= t2
	mov.b 0(r1), r12	;return p2val
	add #4, r1
	pop r0

	


	
