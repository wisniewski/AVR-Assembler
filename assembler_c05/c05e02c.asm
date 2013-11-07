.include "m16def.inc" ;dyrektywa dla preprocesora

.equ liczba1 = 115 ;0x73
.equ liczba2 = 100 ;0x64

ldi r24, low(ramend) ;zaladuj do r16 LSB adresu KONCA pamieci SRAM
out spl, r24 ;sp - wskaznik do stosu, tu LSB, INICJALIZACJA SP
;stack pointer: 0x005f (czyli LSB == 5f)
ldi r24, high(ramend) ;zaladuj do r16 MSB adresu KONCA pamieci SRAM
out sph, r24 ;starsza czesc wskaznika stosu (stack pointer)
;stack pointer: 0x045f (czyli MSB == 04)

ldi r16, low(liczba1)
ldi r17, high(liczba1)
ldi r18, byte3(liczba1)
ldi r19, byte4(liczba1)

ldi r20, low(liczba2)
ldi r21, high(liczba2)
ldi r22, byte3(liczba2)
ldi r23, byte4(liczba2)

call minus ;wynik 0xf1

rjmp pc

minus: ;liczba2 - liczba1
sub r20, r16
sub r21, r17
sub r22, r18
sub r23, r19
ret

;(dec) 100 - 115 = -15
; (u2) 0x64 - 0x73 = 0xf1 
; czyli: 100 - 115 = 241