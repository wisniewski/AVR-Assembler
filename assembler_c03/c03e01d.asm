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