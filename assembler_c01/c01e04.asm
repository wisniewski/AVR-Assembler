.include "m16def.inc" //

ldi r16, 0xff //zaladuj rejestr r16 wartoscia 255 (10) lub 0xff (16)
out ddrb, r16 //rejestr ddrd jako wyjscie (ddrb = 0xff)

//infinity loop
//miganie diodami led, kazda ma inna czestotliwosc swiecenia (najstarsza - najwolniej)
loop: 
	ldi r16, 255
	delay1:
		ldi r17, 255
		delay0:
			dec r17
		brne delay0
		dec r16
	brne delay1
	inc r0
	out portb, r0 //wysylamy do rejestru portb aktualna wartosc r0
rjmp loop
