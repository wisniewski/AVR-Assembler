/*
* Random number by ADC (without stdlib.h)
* Segments from A to DP - PC0 - PC7
* Select digit from 0 to 3 - PB0 - PB3
* Switch (ext int0) - PD2
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

uint16_t volatile seed; //ADC register is 16-bit, not 8-bit
uint8_t volatile random_number[4];

const uint8_t number_segments[10] PROGMEM = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void select_digit(void)
{
	static uint8_t i, j;
	PORTB = (1<<((i++)%4)) ^ 0xf; //select 7seg display (0-3)
	PORTC = pgm_read_byte(&number_segments[random_number[++j%4]]); //show rnd number
}

ISR(TIMER0_COMP_vect)
{
	select_digit();
}

ISR(INT0_vect)
{
	static uint8_t i; //choose only ONE number
	random_number[i++] = seed % 10;
	i %= 4;
}
ISR(ADC_vect)
{
	seed =  (seed<<1); //move left
	seed |= ADC & 0x01; //read and add LSB
}
int main(void)
{
	DDRC = 0xff; //conf ports
	DDRB = 0x0f;
	PORTD |= (1<<PD2); //pull-up resistor
	
	TCCR0 |= (1<<WGM01) | (1<<CS01) | (1<<CS00); //ctc timer0
	OCR0 = 125;
	TIMSK |= (1<<OCIE0);
	
	MCUCR |= (1<<ISC01); //external interrupt, faling edge
	GICR |= (1<<INT0);
	
	ADMUX  = (1<<REFS0); //voltage reference 
	ADCSRA  |=  (1<<ADPS1)|(1<<ADPS0) | (1<<ADPS2); //prescaler
	ADCSRA  |=  (1<<ADEN) | (1<<ADATE) | (1<<ADIE) | (1<<ADSC); //adc conf
	
	sei();
	
	while(1);
	return 0;
}
