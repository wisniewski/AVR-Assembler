.include "m16def.inc" ;dyrektywy dla preprocesora

.equ m = 1
.equ n = 1
.equ k = 1

call sekunda

rjmp pc

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
	ret