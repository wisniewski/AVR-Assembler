.nolist
.include "m16def.inc"
.list

.cseg
.org 0

jmp start

.org INT0addr
rjmp sub_ext_0

.org INT1addr
rjmp sub_ext_1

start:
	cli ;wylaczenie przerwan

	;inicjalizacja stosu
	ldi r16, HIGH(RAMEND)
	out sph, r16
	ldi r16, LOW(RAMEND)
	out spl, r16

	;konf kontrolera przerwan
	ldi r16, 0xc0;
	out GICR, r16
	
	ldi r16, 0xb 
	out MCUCR, r16

	sei ;wlaczenie pezrwan

loop:
	nop
	nop
	nop
	rjmp loop

;podprogram przerwania 0
sub_ext_0: ;INT0 - PD2
	nop
	inc r0
	nop
reti

;podprogram przerwania 1
sub_ext_1: ;INT1 - PD3
	nop
	dec r0
	nop
reti
