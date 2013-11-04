----------------------------------------------------------------------------------
1.2 / 2(c)
----------------------------------------------------------------------------------

.include "m16def.inc"

ldi r16, 0xab //2-byte: ea0b ; 1-byte: 0b ea (little endian)
ldi r18, 0xcd //2-byte: ec2d ; 1-byte: 2d ec (little endian)

mov r0, r16 //skopiuj z r16 do r0 //00 2e <- 0, czyli r16
mov r1, r18 //analogicznie jak u gory //12 2e <- 2, czyli r18

rjmp pc //infinity loop

----------------------------------------------------------------------------------
1.2 / 3(a)
----------------------------------------------------------------------------------

.include "m16def.inc"

ldi r16, 0x34 //laduje do rejestru r16
ldi r17, 0x12

mov r0, r16 //kopiuje czesc mlodsza do r0
mov r1, r17

rjmp pc //infinity loop

----------------------------------------------------------------------------------
1.2 / 3(b)
----------------------------------------------------------------------------------

.include "m16def.inc"

ldi r16, 0x34 //laduje do rejestru r16
ldi r17, 0x12

movw r1:r0,r17:r16 //uzycie instrukcji movw (kopiuje cale slowo)

rjmp pc //infinity loop
