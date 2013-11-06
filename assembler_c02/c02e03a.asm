.include "m16def.inc"

ldi r16, 0x34 //laduje do rejestru r16
ldi r17, 0x12

mov r0, r16 //kopiuje czesc mlodsza do r0
mov r1, r17

rjmp pc //infinity loop