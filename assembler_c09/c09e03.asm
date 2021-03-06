;eleminacja wplywu dgran stykow
;dwa przyciski - PC0 oraz PC1
;wyswietlam stan na portcie B

.nolist
.include "m16def.inc"
.list

.cseg
.org 0

cli
ldi r16, HIGH(RAMEND)
out sph, r16
ldi r16, LOW(RAMEND)
out spl, r16
sei

ldi r16, 0xff
out DDRB, r16 ;jako wyjscie
ldi r16, 0x00
out PORTB, r16 ;stan niski na B

cbi DDRC, 0 ;jako wejscie (domyslnie)
sbi PORTC, 0 ;jako wejscie z pull-upem

loop:
	clt
	sbis PINC, 0
	call debouncing
	rjmp loop

debouncing:
	set
	call czekaj
	call czekaj
	sbic PINC, 0
	brts increase
	ret

increase:
	inc r16
	out PORTB, r16
	rjmp loop

czekaj:
 ldi R20, 0
 czekaj125ms_0:
  ldi R21, 0
  czekaj125ms_1:
   inc R21
   cpi R21, 250
   brlo czekaj125ms_1
  inc R20
  cpi R20, 125
  brlo czekaj125ms_0
 ret