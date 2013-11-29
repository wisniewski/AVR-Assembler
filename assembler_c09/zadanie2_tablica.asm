;przesuwanie bitu w prawo lub w lewo

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
out DDRB, r16 ;jako wyjscie
ldi r16, 0x02
out PORTB, r16 ;stan niski na B

cbi DDRC, 0 ;jako wejscie (domyslnie)
cbi DDRC, 1 ;jako wejscie (domyslnie)
sbi PORTC, 0 ;jako wejscie z pull-upem
sbi PORTC, 1 ;jako wejscie z pull-upem

.equ m = 50
.equ n = 50
.equ k = 50

loop:
	clt
	sbis PINC, 0
	call debouncing_inc
	sbis PINC, 1
	call debouncing_dec
	rjmp loop

debouncing_inc:
	set
	call sekunda
	call sekunda
	sbis PINC, 0
	brts increase
	ret

increase:
	
	call prawo
	out PORTB, r16
	rjmp loop

debouncing_dec:
	set
	call sekunda
	call sekunda
	sbis PINC, 1
	brts decrease
	ret

decrease:
	
	call lewo
	out PORTB, r16
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
        ;out porta, r26
ret

prawo:
	rol r16
	ret
lewo:
	ror r16
	ret