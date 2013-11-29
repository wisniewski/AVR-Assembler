.include "m16def.inc" ;dyrektywy dla preprocesora
 
ldi r16, 0xff ;255
out ddra, r16 ; cale ddra jako wyjscie

out porta, r16

ldi r16, 0x00
out ddrb, r16 ;jako wejscia

ldi r16, 0xc0 ;0b1100 0000

loop:
	in r0, pinb ;wrzuc do r0 stan na pinie b
	eor r0, r16 ;XOR dla dwoch najstarszych bitow
	out porta, r0 ;wrzuc ta wartosc do portu a (jesli nic nie podlaczone to stan niski)

rjmp loop

rjmp pc