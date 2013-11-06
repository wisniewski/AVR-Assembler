.include "m16def.inc"

clr r16 //albo ldi r16, 0x00
ser r17 //albo ldi r17, 0xff

sts DDRA+32, r16 // DDRA = 0x00
sts PORTA+32, r17 // PORTA = 0xFF
lds r0, PINA+32 //zmienna = PINA