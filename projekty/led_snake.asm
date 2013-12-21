;Zrealizuj projekt wê¿a œwietlnego (wêdruj¹ce 3 diody) w¹¿ zrealizowany 
;w oparciu o ten zestaw z uczelni. Czêstotliwoœæ prze³¹czania diod zmieniana 
;za pomoc¹ dwóch dowolnie wybranych przycisków .jeden z nich ma zwiêkszaæ drugi.
;zmniejszaæ .wykorzystaæ.do tego celu uk³ad licznika czasomierza T0.projekt 
;zrealizowaæ w oparciu o przerwan.

.nolist
.include"m32def.inc"
.list

.cseg
.org 0

jmp initiation

.org INT0addr ;three interrupts vectors
rjmp button0

.org INT1addr
rjmp button1

.org OC0addr
rjmp timer

initiation:
	cli ;block interrupts

	ldi r16, HIGH(RAMEND) ;stack pointer
	out sph, r16
	ldi r16, LOW(RAMEND)
	out spl, r16
	
	;timer0 ctc, prescaler 1024, 10 miliseconds interrupt
	ldi r16, (1<<WGM01) | (1<<CS02) | (1<<CS00)
	out TCCR0, r16
	ldi r16, (1<<OCIE0)
	out TIMSK, r16
	ldi r16, 77 
	out OCR0, r16

	ldi r17, 100 ;frequency ca. 1 second
	ldi r18, 0x07
	ldi r19, 5
	ldi r20, 5

	;external interrupts - pd2 and pd3
	ldi r16, (1<<ISC11) | (1<<ISC01)
	out MCUCR, r16
	ldi r16, (1<<INT0) | (1<<INT1)
	out GICR, r16

	sbi PORTD, 2 ;pull-up resistor
	sbi PORTD, 3

	ldi r16, 0xff ;enable led_snake
	out DDRA, r16
	out PORTA, r18
	
	sei ;enable interrupts

loop: ;empty infinite loop
	rjmp loop

timer: 
	cpi r17, 0 ;if (!r17)
	breq shift ;let's shift our led snake!
	dec r17
	reti

shift:
	cpi r19, 0
	brne led_snake_left ;if counter still dec
	cpi r19, 0 ;if (!r19)
	breq led_snake_right ;if counter is 0
	reti
	
led_snake_left:
	rol r18 ;shift left
	out PORTA, r18
	ldi r17, 100 ;again wait second
	dec r19 ;counter--
	reti

led_snake_right:
	cpi r20, 0 ;if counter is still dec
	brne right
	ldi r19, 5 ;counters
	ldi r20, 5
	reti

right:
	ror r18 ;shift right
	out PORTA, r18	
	ldi r17, 100 ;wait second
	dec r20 ;counter--
	reti

button0: ;INT0 interrupt
	ldi r16, 10 ;faster
	out OCR0, r16
	reti

button1: ;INT1 interrupt
	ldi r16, 150 ;slower
	out OCR0, r16
	reti

