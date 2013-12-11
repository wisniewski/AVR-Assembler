;overflow
.nolist
.include "m32adef.inc"
.list

.cseg
.org 0

jmp start

;dla ATmegi16 to $012 !!!!!!!!!!
.org $016 ;Timer/Counter0 Overflow
rjmp sub_ext_0

start:
	cli ;wylaczenie przerwan

	;inicjalizacja stosu
	ldi r16, HIGH(RAMEND)
	out sph, r16
	ldi r16, LOW(RAMEND)
	out spl, r16

	sbi ddrc, 0
	cbi portc, 0

	;-- konf kontrolera przerwan --
	
	;overflow
	ldi r16, (1<<TOIE0)
	out TIMSK, r16
	;compare match
	ldi r16, (1<<OCIE0)
	out TIMSK, r16

	;preskaler (u mnie generuje okolo 0,5 sekundy)
	ldi r16, (1<<CS02) | (1<<CS00)
	out TCCR0, r16 
	
	;do XORa dla ledow
	ldi r18, 1

	sei ;wlaczenie przerwan

loop:
	rjmp loop

;Timer/Counter0 Overflow
sub_ext_0:
	in r16, portc
	eor r16, r18
	out portc, r16
	nop
reti
