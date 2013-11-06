.include "m16def.inc"

ldi r16, 0xab //2-byte: ea0b ; 1-byte: 0b ea (little endian)
ldi r18, 0xcd //2-byte: ec2d ; 1-byte: 2d ec (little endian)

mov r0, r16 //skopiuj z r16 do r0 //00 2e <- 0, czyli r16
mov r1, r18 //analogicznie jak u gory //12 2e <- 2, czyli r18

rjmp pc //infinity loop