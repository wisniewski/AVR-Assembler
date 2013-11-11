.include "m16def.inc" ;dyrektywy dla preprocesora

.equ m = 100
.equ n = 135
.equ k = 197

ldi r16, 0xff
out ddra, r16
ldi r17, 0x00

sekunda:
	ldi r17, m
	loop2:
		ldi r16, n
		loop1:
				ldi r18, k
				loop3:
				dec r18
				brne loop3
		dec r16
		brne loop1
	dec r17
	brne loop2
	inc r17
	out porta, r17

rjmp sekunda