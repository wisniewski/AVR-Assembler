;dyrektywy dla preprocesora
.equ a = 100; przypisz do zmiennej a wartosc 100
.equ b = 200; analogicznie / -56 w kodzie U2

;ladowanie wartosci do rejestrow
ldi r16, a; zaladuj do rejestru 16 wartosc 100
ldi r17, b; analogicznie

;znacznik Carry
add r16, r17; dodaj obie liczby, wynik zapisz w r16
;wychodzi 0x2c czyli 44 - OK, bo 100 + (-56) = 44
rjmp pc; infinity loop

NKB				U2				A+B				C		V
A		B		A		B		NKB		U2		
0		0		0		0		0		0		0		0
100		100		100		100		200		-56		0		1
250		200		-6		-56		194		-62		1		0
64		64		64		64		128		-128	0		1
128		128		-128	-128	0		0		1		1
255		255		-1		-1		254		-2		1		0
128		255		-128	-1		127		127		1		1
