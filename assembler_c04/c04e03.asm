;dyrektywy dla preprocesora
.equ a = 29
.equ b = 38

;ladowanie wartosci do rejestrow
ldi r16, a
ldi r17, b

add r16, r17

rjmp pc; infinity loop

Komentarz:
H - Half Carry - w trakcie operacji na licznach DEC zapisanych w kodzie binarnym (np. BCD) nastepuje
przeniesienie pomiedzy m³odsza a starsza polowk¹ bajtu wyniku

Tabela: 
DEC				BCD						H
A		B		A			B	
29		38		00101001	00111000	1
11		33		00010001	00110011	0
25		35		00100101	00110101	0
90		20		10010000	00100000	0

Dodawanie BCD:
29			0010	1001
38			0011	1000
+			0110	0001
poprawka	0000	0110
			0110	0111
			6		7
			
Wprowadzam korekcje - dlaczego?
a) cyfra dziesiatek jest wiêksza od 9 (1001)
b) gdy w trakcie dodawania wystapilo przeniesienie (przy odejmowaniu pozyczka) do sasiedniej grupy bitow !!!