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
sub r20, r16; odejmij r16 od r20, wynik: 0x11 
sbc r21, r17; 0x00
sbc r22, r18; 0xed
sbc r23, r19; 0x00
;po odjêciu (dec) -> 15532049
;hex -> ED0011 czyli zgadza sie z wynikiem dziesietnym

;bez carry (same polecenia sub) wynik wyglada nastepujaco: 0x01ed0011

rjmp pc; infinity loop