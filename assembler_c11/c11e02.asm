;1 sposób mój ulubiony:
;konf kontrolera przerwan
ldi r16, 0xc0;
out GICR, r16
ldi r16, 0xb 
out MCUCR, r16 

;2 sposób, bardziej przejrzysty
ldi r16, (1<<INT0) | (1<<INT1)
out GICR, r16

ldi r16, (1<<ISC01) | (1<<ISC00) | (1<<ISC11)
out MCUCR, r16