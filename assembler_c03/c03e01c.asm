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