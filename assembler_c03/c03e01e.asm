.include "m16def.inc"

ldi r16, 0xab
ldi r17, 0xcd

sts dmem, r16 //wpisalo ab pod adres 0x100 w pamieci sram
sts 0, r17 //wpisalo do rejestru zero wartosc z r17

lds r18, dmem //wpisalo do rejestru r18 wartosc ab z adresu 0x100
lds r18, 17 //a teraz wpisalo cd, bo z rejestru 17

//rezerwacja 16 najtow od miejsca 0x100, a nie 0x60 jak w poprzednich programach
.dseg
.org 0x100
dmem: .byte 16 