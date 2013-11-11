.include "m16def.inc"
 
.equ a = 115 ;liczba u2 -> 0x73
.equ b = 100 ;liczba u2 -> 0x64

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

call minus

rjmp pc; infinity loop

minus:
	sub r20, r16; 0xf1
	sbc r21, r17; 0xff
	sbc r22, r18; 0xff
	sbc r23, r19; 0xff
	ret
	;100 - 115 = -15 
	;-15 w u2 -> 241 (0xf1)