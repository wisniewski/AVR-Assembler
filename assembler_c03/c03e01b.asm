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