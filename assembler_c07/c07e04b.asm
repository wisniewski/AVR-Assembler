.include "m16def.inc" ;dyrektywy dla preprocesora
 
ldi r16, 0xff
out ddra, r16 ;cale jako wyjscie

loop:
	inc r20 ;zwieksz o 1
	out porta, r20 ;ustawianie bitow
	nop
	nop ;w sumie wystarczy jeden nop, ale dla pewnosci daje dwa
	in r0, pina ;odczytana dobra wartosc

rjmp loop