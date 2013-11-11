.include "m16def.inc" ;dyrektywy dla preprocesora

.equ m = 100
.equ n = 135
.equ k = 197

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

rjmp pc

;wzor 3mnk + 3mn + 3m = 8 019 300
; f = n / t
; n = f * t
; n = 8000000 * 1s = 8000000