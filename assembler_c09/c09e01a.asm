;inna wersja do zadania 1
;zwiekszanie ledow na porcie D jak naciskamy przycisk dolaczony do PC0

.nolist
.include "m16def.inc"
.list

.cseg
.org 0

cli
ldi r16, HIGH(RAMEND)
out sph, r16
ldi r16, LOW(RAMEND)
out spl, r16
sei

ldi r16, 0xff
out DDRD, r16 ;jako wyjscie
ldi r16, 0x00
out PORTD, r16 ;stan niski na B

cbi DDRC, 0 ;jako wejscie (domyslnie)
sbi PORTC, 0 ;jako wejscie z pull-upem

loop:
	sbis PINC, 0
	rjmp increase
	rjmp loop

increase:
	inc r16
	out PORTD, r16
	rjmp loop
