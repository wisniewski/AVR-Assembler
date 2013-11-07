.include "m16def.inc" ;dyrektywa dla preprocesora

ldi r16, low(ramend) ;zaladuj do r16 LSB adresu KONCA pamieci SRAM
out spl, r16 ;sp - wskaznik do stosu, tu LSB, INICJALIZACJA SP
;stack pointer: 0x005f (czyli LSB == 5f)
ldi r16, high(ramend) ;zaladuj do r16 MSB adresu KONCA pamieci SRAM
out sph, r16 ;starsza czesc wskaznika stosu (stack pointer)
;stack pointer: 0x045f (czyli MSB == 04)
nop
call podprogram2 ;wywolaj podprogram
nop ;SP: 0x045f
call podprogram1
;po wywolaniu ;SP: 0x045d
nop

rjmp pc ;infinity loop

podprogram1: ;SP: 0x045b
	nop
	nop
	ret

podprogram2: ;SP: 0x045d
	nop
	call podprogram1
	nop ;SP: 0x045d
	call podprogram1
	nop ;SP: 0x045d
	ret

;Stos przetrzymuje zmienne lokalne oraz zapamietuje adresu 
;powrotu przy wywolaniu podprogramow (tzw slady)

;Pamiec stosu wymaga wskaznika stosu - SP - rejestr ktory okresla adres w 
;pamieci SRAM pod ktory zostanie cos zapisane. 
;64 kB - zatem trzeba podzielic na czesc mlodsza SHL i starsza SPH

;korelacja pomiedzy PC, a wartoscia odkladana na stos: istnieje
;zaobserwowane: LSB PC jest odkladany jako wartosc na stos