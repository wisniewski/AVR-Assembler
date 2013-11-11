.include "m16def.inc"
 
.equ a = 0x1e6 ;liczba 486
.equ b = 0x2e6 ;liczba 742

ldi r24, low(ramend) ;zaladuj do r16 LSB adresu KONCA pamieci SRAM
out spl, r24 ;sp - wskaznik do stosu, tu LSB, INICJALIZACJA SP
;stack pointer: 0x005f (czyli LSB == 5f)
ldi r24, high(ramend) ;zaladuj do r16 MSB adresu KONCA pamieci SRAM
out sph, r24 ;starsza czesc wskaznika stosu (stack pointer)
;stack pointer: 0x045f (czyli MSB == 04)
 
ldi r16, low(a); zaladuj do rejestru
ldi r17, high(a); analogicznie
ldi r18, byte3(a)
ldi r19, byte4(a)

ldi r20, low(b); zaladuj do rejestru
ldi r21, high(b); analogicznie
ldi r22, byte3(b)
ldi r23, byte4(b)

call plus

rjmp pc; infinity loop

plus:
	add r20, r16; 0xcc
	adc r21, r17; 0x04
	adc r22, r18; 0x00
	adc r23, r19; 0x00
	ret
	;wynik dec -> 1228
	;wynik u2 -> 0x4cc czyli OK!