.include "m16def.inc"

clr r16 //albo ldi r16, 0x00
ser r17 //albo ldi r17, 0xff

out DDRA, r16 // DDRA = 0x00
out PORTA, r17 // PORTA = 0xFF
in r0, PINA //zmienna = PINA