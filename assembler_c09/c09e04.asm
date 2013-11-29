;przyciski:
; dodaj 1 - PC0
; odejmuj 1 - PC1
; zeruj bity - PC2
; ustaw liczbe 128 - PC3
; na porcie D LEDy

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
out DDRC, r16
ldi r16, 0x0f
out PORTC, r16

.equ m = 50
.equ n = 50
.equ k = 50

ldi r16, 0xff
out PORTD, r16 ;stan niski na B

loop:
	clt
	sbis PINC, 0
	call debouncing_inc
	sbis PINC, 1
	call debouncing_dec
	sbis PINC, 2
	call debouncing_zero
	sbis PINC, 3
	call debouncing_set_bits
	rjmp loop

debouncing_inc:
	set
	call sekunda
	call sekunda
	sbis PINC, 0
	brts increase
	ret
debouncing_dec:
	set
	call sekunda
	call sekunda
	sbis PINC, 1
	brts decrease
	ret
debouncing_set_bits:
	set
	call sekunda
	call sekunda
	sbis PINC, 3
	brts set_bits
	ret
debouncing_zero:
	set
	;call sekunda
	;call sekunda
	sbis PINC, 2
	brts zero
	ret

increase:
	inc r16
	out PORTD, r16
	rjmp loop
decrease:
	dec r16
	out PORTD, r16
	rjmp loop
set_bits:
	ldi r16, 128
	out PORTD, r16
	rjmp loop
zero:
	ldi r16, 0x00
	out PORTD, r16
	rjmp loop

sekunda:
	ldi r26, m
	loop2:
		ldi r25, n
        loop1:
			ldi r27, k
            loop3:
            dec r27
            brne loop3
		dec r25
		brne loop1
	dec r26
	brne loop2
	inc r26
ret
