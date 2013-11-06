.include "m16def.inc"

ldi zl, low(cmem<<1) 
//wpisanie do mlodszej czesci rejestru Z, czyli r30
//czego? ano 0x06, czyli adres
ldi zh, high(cmem<<1) //wpisanie do czesci starszej (r31) 0x00 (nie ma zmiany)

lpm r0, z //laduje do rejestru bajt z pamięci programu (flash),
//ktory ma adres w rejestrze Z
lpm r1, z+ //to samo, ale zwiekszam Z (increase)
lpm r2, z  //tu juz sie pojawi inna wartosc, bo zwiekszylismy Z

rjmp pc //infinity loop

//wpisanie do pamieci flash
.cseg
cmem: .db "ABCD ", 0