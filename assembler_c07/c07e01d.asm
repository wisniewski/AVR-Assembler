.include "m16def.inc" ;dyrektywy dla preprocesora
 
ldi r16, 0xff ;255
out ddra, r16 ; cale ddra jako wyjscie

ldi r16, 0x55
out porta, r16 ;co drugi pin ma stan wysoki

rjmp pc