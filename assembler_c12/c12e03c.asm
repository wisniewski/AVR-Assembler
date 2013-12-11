;overflow
.nolist
.include "m32adef.inc"
.list

.cseg
.org 0

jmp start

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

	;konfiguracja timera0 w trybie fast PWM
	ldi r16, (1 << CS01) | (1 << CS00) | (1 << WGM00) | (1 << WGM01) | (1 << COM01);
	out TCCR0, r16 

	;compare match
	ldi r16, (1<<OCIE0)
	out TIMSK, r16

	;wartosc modulowana dla PWMa
	ldi r16, 255
	out OCR0, r16 

	sbi DDRB, 3 ;ustawianie wyjscia OC0 jako wyjscie

	sei ;wlaczenie przerwan

loop:
	rjmp loop

;fast pwm
sub_ext_0:
	nop
reti
