.include "m16def.inc"

ldi r16, 0x34 //laduje do rejestru r16
ldi r17, 0x12

movw r1:r0,r17:r16 //uzycie instrukcji movw (kopiuje cale slowo)

rjmp pc //infinity loop
