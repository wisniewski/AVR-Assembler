Jakie rejestry obslugi przerwan zewnetrznych?
Dokumentacja i rozdzial External Interrupts: rejestry GICR (od aktywacji
INT0 oraz INT1) i rowniez osmiobitowy rejestr MCUCR (od konf. zboczy).

GICR - bit 6 i 7. Heksadecymalnie: 0xc0
MCUCR:
INT0 - zbocze narastajace - ustawione bity ISC01 i ISC00
INT1 - zbocze opadajace - ustawiony ISC11, wyzerowany ISC10
Heksadecymalnie: 0xb (to samo co 0x0b)

W kodzie odpowiada za to:
	
;konf kontrolera przerwan
ldi r16, 0xc0;
out GICR, r16
	
ldi r16, 0xb 
out MCUCR, r16 