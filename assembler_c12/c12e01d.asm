;overflow
.nolist
.include "m16def.inc"
.list

.cseg
.org 0

jmp start

.org OVF0addr ;Timer/Counter0 Overflow
rjmp sub_ext_1

.org OC0addr ;Timer/Counter0 Compare Match
rjmp sub_ext_0

start:
	cli ;wylaczenie przerwan

	;inicjalizacja stosu
	ldi r16, HIGH(RAMEND)
	out sph, r16
	ldi r16, LOW(RAMEND)
	out spl, r16

	;-- konf kontrolera przerwan --
	
	;overflow i compare match
	ldi r16, (1<<TOIE0) | (1<<OCIE0)
	out TIMSK, r16

	;preskaler (fmax)
	ldi r16, (1<<CS00)
	out TCCR0, r16 

	ldi r16, 0x0f
	out OCR0, r16 
	
	;dla tcnc0
	ldi r18, 0xf0

	sei ;wlaczenie przerwan

loop:
	rjmp loop

;Timer/Counter0 Compare Match
sub_ext_0:
	inc r16
	ldi r17, 0xa0;
	in r18, TCNT0
	add r17, r18
	out TCNT0, r17
reti

;Timer/Counter0 Overflow
sub_ext_1:
	dec r16
reti
