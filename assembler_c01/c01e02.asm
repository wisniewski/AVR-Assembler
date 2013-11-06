.include "m16def.inc" 

//programista inicjalizuje stos w uC poprzez wgranie adresu stosu (poczatek)
//na wskaznik stosu
ldi r16, low(ramend) //wrzucenie do rejestru 16 wartosci LSB slowa 16-biowego
//uC sa 8-bitowe, zatem musimy rozdzielosc slowo na mlodsza i starsza czesc
//ramend reprezentuje adres ostatniej lokacji pamiesci sram
out spl, r16 //stack pointer low
ldi r16, high(ramend)
out sph, r16 //stack pointer high

call podprogram //wywolanie "podfunkcji"

ldi r16, 0xab //wgraj do rejestru r16 wartosc heksadecymalna 0xab
mov r0, r16 //skopiuj zawartosc do r0
inc r0 //zwieksz r0 o 1

koniec: //infinity loop
rjmp koniec

podprogram:
	nop
	ret

.dseg //pamiec sram
dmem: .byte 7

.cseg //pamiec flash
cmem: .db "ABCD ", 0

.eseg //pamiec eeprom
emem: .db "1234", 0