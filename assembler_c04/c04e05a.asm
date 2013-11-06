;dyrektywy dla preprocesora
.equ a = 100
.equ b = 100

;ladowanie wartosci do rejestrow
ldi r16, a
ldi r17, b

sub r16, r17

rjmp pc; infinity loop

Liczby C(1) i V(0): 
0 i 255
128 i 129

Carry:
Gdy w trakcie odejmowania wyst¹pila pozyczka do sasiedniej grupy bitow.