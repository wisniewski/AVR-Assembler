----------------------------------------------------------------------------------
1.1 / 2(a)
----------------------------------------------------------------------------------
.include "m16def.inc" //

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

----------------------------------------------------------------------------------
1.1 / 4(a)
----------------------------------------------------------------------------------

.include "m16def.inc" //

ldi r16, 0xff //zaladuj rejestr r16 wartoscia 255 (10) lub 0xff (16)
out ddrb, r16 //rejestr ddrd jako wyjscie (ddrb = 0xff)

//infinity loop
//miganie diodami led, kazda ma inna czestotliwosc swiecenia (najstarsza - najwolniej)
loop: 
	ldi r16, 255
	delay1:
		ldi r17, 255
		delay0:
			dec r17
		brne delay0
		dec r16
	brne delay1
	inc r0
	out portb, r0 //wysylamy do rejestru portb aktualna wartosc r0
rjmp loop
