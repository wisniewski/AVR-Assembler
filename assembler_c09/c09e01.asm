.nolist ;nie listuj pliku z include'a
.include "m16def.inc"
.list
.cseg ;program od 0 adresu
.org 0

cli ;wylaczenie przerwan
ldi r16, HIGH(RAMEND) ;implementacja stosu (stack pointer)
out sph, r16
ldi r16, LOW(RAMEND)
out spl, r16
sei ;wlaczenie przerwan

ldi r16, 0xff
out DDRD, r16 ;jako wyjscie D

cbi DDRC, 0 ;jako wejscie (domyslnie)
sbi PORTC, 0 ;jako wejscie z pull-upem

ldi r16, 0x01
ldi r17, 0x01 ;potrzebny do XORa

loop:
	sbis PINC, 0 ;pomin jesli nie naciskamy
	call turn_off
	out PORTD, r16
	rjmp loop
	
turn_off:
	eor r16, r17 ;XOR rejestru 16 z 17
	out PORTD, r16 ;wyslij stan na portD
