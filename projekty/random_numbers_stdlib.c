#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdlib.h>

volatile uint8_t random_number[4];
const uint8_t number_segments[10] PROGMEM = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void select_digit(void)
{
	static uint8_t i, j;
	PORTB = (1<<((i++)%4)) ^ 0xf; //select 7seg display (0-3)
	PORTC = pgm_read_byte(&number_segments[random_number[++j%4]]); //show rnd number
}

ISR(TIMER0_COMP_vect)
{
	select_digit(); //1 ms is enough to trick human eye
}

ISR(INT0_vect)
{
	for(int i=0; i<4; i++)
	random_number[i] = rand() % 10; //choose rnd number
}

int main(void)
{
	DDRC = 0xff; //conf ports
	DDRB = 0x0f;
	PORTD |= (1<<PD2); //pull-up resistor
	
	TCCR0 |= (1<<WGM01) | (1<<CS01) | (1<<CS00); //ctc timer0
	OCR0 = 125;
	TIMSK |= (1<<OCIE0);
	
	MCUCR |= (1<<ISC01); //external interrupt (pd2 - int0)
	GICR |= (1<<INT0);
	
	sei(); //enable interrupts
	
	while(1);
	return 0;
}
