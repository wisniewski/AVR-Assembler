.include "m16def.inc" ;dyrektywy dla preprocesora
 
;ldi - pc + 1
;dec - pc + 1
;brne - pc + k + 1
;if false -> pc + 1

.equ n = 5
.equ m = 2

ldi r17, m
loop2:
	ldi r16, n
	loop1:
		dec r16
	brne loop1
	dec r17
brne loop2

rjmp pc

;Po modyfikacji program nie bedzie dzialal jak nalezy - szybciej sie zakonczy petla