;overflow
.nolist
.include "m16def.inc"
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

	;konfiguracja timera0 w trybie CTC 1kHz, czyli do uzyskania liczba 8k
	ldi r16, (1 << CS01) | (1 << CS00) | (1 << WGM01) | (1 << COM00);
	out TCCR0, r16 

	;compare match
	ldi r16, (1<<OCIE0)
	out TIMSK, r16

	;8000 = 64*124+1
	ldi r16, 124
	out OCR0, r16 

	sbi DDRB, 3 ;ustawianie wyjscia OC0 jako wyjscie
	
	ldi r16, 0xf ;konfiguracja przyciskow
	out DDRC, r16
	out PORTC, r16

	sei ;wlaczenie przerwan

loop:
	rjmp loop

;CTC
sub_ext_0:
	sbis PINC, 0
	call freq0
	sbis PINC, 1
	call freq1
	sbis PINC, 2
	call freq2
	sbis PINC, 3
	call freq3
reti

freq0:
	cbi PORTB, 4
	ldi r16, 10
	out OCR0, r16 
	ret

freq1:
	ldi r16, 80
	out OCR0, r16 
	ret

freq2:
	ldi r16, 150
	out OCR0, r16 
	ret

freq3:
	ldi r16, 255
	out OCR0, r16 
	ret
