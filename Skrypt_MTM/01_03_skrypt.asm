----------------------------------------------------------------------------------
1.3 / 1(a)
----------------------------------------------------------------------------------

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

----------------------------------------------------------------------------------
1.3 / 1(b)
----------------------------------------------------------------------------------

.include "m16def.inc"

ldi xl, low(dmem)
ldi xh, high(dmem)

ldi r16, dmem_end-dmem //zaladowanie do r16 wielosci zarezerwowanej pamieci

loop:
	st x+, r0 //przesuwamy sie o 1 dalej w pamieci i piszemy tam wartosc r0; x to wskaznik do lokacji w pamieci
	inc r0 //zwiekszam r0
	dec r16 //zmniejszam r16, aby uzyskac znacznik -> wtedy przejde do rmjp
brne loop

rjmp pc

//rezerwacja 8 bajtow, cos jak malloc() w C
.dseg
dmem: .byte 8
dmem_end:

----------------------------------------------------------------------------------
1.3 / 1(c)
----------------------------------------------------------------------------------

.include "m16def.inc"

ldi xl, low(dmem)
ldi xh, high(dmem)

ldi zl, low(cmem<<1)
ldi zh, high(cmem<<1)

ldi r16, dmem_end-dmem //zaladowanie do r16 wielosc zarezerwowanej pamieci

loop:
	lpm r0, z+
	//kopiuje bajty z pamieci flash do rejestrow
	
	st x+, r0
	//kopiuje bajty z rejestrow do pamieci sram

	inc r0
	//zwiekszam r0
	
	dec r16 //zmniejszam r16, aby uzyskac znacznik -> wtedy przejde do rmjp, czyli od 5 do 0
brne loop

rjmp pc

//rezerwacja 5 bajtow, cos jak malloc() w C
.dseg
dmem: .byte 5
dmem_end:

//wpisanie do pamieci flash, atrybut PROGMEM w C
.cseg
cmem: .db "12345", 0

----------------------------------------------------------------------------------
1.3 / 1(d)
----------------------------------------------------------------------------------

.include "m16def.inc"

ldi xl, low(dmem)
ldi xh, high(dmem)

ldi zl, low(cmem<<1)
ldi zh, high(cmem<<1)

ldi r16, dmem_end-dmem //zaladowanie do r16 wielosc zarezerwowanej pamieci

//najpierw kopiuje dane z pamieci flash do sram, zeby nie wpisywac recznie
loop:
	lpm r0, z+
	//kopiuje bajty z pamieci flash do rejestrow
	st x+, r0
	//kopiuje bajty z rejestrow do pamieci sram
	inc r0
	//zwiekszam r0
	dec r16 //zmniejszam r16, aby uzyskac znacznik -> wtedy przejde do rmjp, czyli od 5 do 0
brne loop

//teraz chce te dane skopiowac w inne miejsce pamieci flash (inny adres) w odwrotnej kolejnosci

ldi xl, $65 //adres 5
ldi r16, dmem_end-dmem //znowu jakby zmienna = 5

ldi zl, $80 //inny adres w pamieci sram

loop2:
	ld r0, -x //dzieki temu poruszamy sie od 5, 4, 3 do 1
	st z+, r0 //zwiekszamy swoj adres, czyli $81, $82 itd
	inc r0

	dec r16 //zmniejszam r16, aby uzyskac znacznik -> wtedy przejde do rmjp, czyli od 5 do 0
brne loop2

rjmp pc

//rezerwacja 5 bajtow, cos jak malloc() w C
.dseg
dmem: .byte 5
dmem_end:

//wpisanie do pamieci flash, atrybut PROGMEM w C
.cseg
cmem: .db "12345", 0

----------------------------------------------------------------------------------
1.3 / 1(e)
----------------------------------------------------------------------------------

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

----------------------------------------------------------------------------------
1.3 / 1(f)
----------------------------------------------------------------------------------

.include "m16def.inc"

clr r16 //albo ldi r16, 0x00
ser r17 //albo ldi r17, 0xff

out DDRA, r16 // DDRA = 0x00
out PORTA, r17 // PORTA = 0xFF
in r0, PINA //zmienna = PINA

----------------------------------------------------------------------------------
1.3 / 1(g)
----------------------------------------------------------------------------------

.include "m16def.inc"

clr r16 //albo ldi r16, 0x00
ser r17 //albo ldi r17, 0xff

sts DDRA+32, r16 // DDRA = 0x00
sts PORTA+32, r17 // PORTA = 0xFF
lds r0, PINA+32 //zmienna = PINA
