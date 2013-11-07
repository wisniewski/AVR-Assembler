.include "m16def.inc" ;dyrektywa dla preprocesora

.equ liczba1 = 0x1e6 ;486
.equ liczba2 = 0x2e6 ;742

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

call plus
;wynik: 0x03cc = 972

rjmp pc

plus:
add r20, r16
add r21, r17
add r22, r18
add r23, r19
ret

; (dec) 486 + 742 = 1588
; (u2) 
; 0x01 + 0x02 => 1 + 2 = 3 => 0x03
; 0xe6 + 0xe6 => -26 - 26 = -52 => 0xCC