;a) NKB
;Dodawanie: Carry
;Odejmowanie: Carry
;PROGRAM ILUSTRUJ¥CY DLACZEGO:

.include "m16def.inc"
 
.equ a = 0x12341122 ;liczba 16bitowa (dec) -> 305402146
.equ b = 0x13211133 ;liczba 16bitowa (dec) -> 320934195
 
;ladowanie wartosci do rejestrow
ldi r16, low(a); zaladuj do rejestru
ldi r17, high(a); analogicznie
ldi r18, byte3(a)
ldi r19, byte4(a)

ldi r20, low(b); zaladuj do rejestru
ldi r21, high(b); analogicznie
ldi r22, byte3(b)
ldi r23, byte4(b)
 
;znacznik Carry
add r20, r16; dodaj obie liczby, wynik: 0x55
adc r21, r17; 0x22
adc r22, r18; 0x55
adc r23, r19; 0x25
;po dodaniu (dec) -> 626336341
;hex -> 0x25552255 czyli zgadza sie z wynikiem dziesietnym

rjmp pc; infinity loop