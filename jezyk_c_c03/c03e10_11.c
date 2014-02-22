/* Sprawdzanie juz na wyswietlaczach 7segmentowych, u mnie s¹ na tranzustorach pnp steruj¹cymi anody wyswietlaczy
uzycie timera w trybie CTC oraz zapisanie cyfry w pamieci FLASH (biblioteka pgmspace) */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

const uint8_t digits_segment[10] PROGMEM = {192, 249, 164, 176, 153, 146, 130, 248, 128, 144}; //exercise 3
uint8_t digits[4]={0}; //exercise 2

uint16_t power(uint16_t base, uint8_t exp)
{
	if(!exp)
	return 1;
	else if(exp)
	return base * power(base, exp-1);
	
	return 0;
}

void digits_get(uint16_t *num, uint8_t tab[]) //exercise 5
{
	for(uint8_t i = 0; i<4; i++)
	{
		*tab++ = (*num / power(10, i)) % 10;
	}
}

void digits_show(void) //exercise 6
{
	static uint8_t i;
	PORTB = 0xff;
	PORTB = 0x0f ^ (1<<(++i%4));
	PORTC = pgm_read_byte(&digits_segment[digits[i%4]]);
}

ISR(TIMER0_COMP_vect) //exercise 7
{
	static uint16_t number;
	static uint8_t mode, key, time;
	key = PINA & 0x0f;
	
	if(!time) //exercise 10-11
	{
		if(key != 15) //read button
		{
			switch(~key & 0x0f)
			{
				case 1: mode = 1; break;
				case 2: mode = 2; break;
				case 4: mode = 4; break;
				case 8: mode = 8; break;
			}
		}
		
		switch(mode) //do job
		{
			case 1: number++; break; //increase
			case 2: ; break; //do nothing, stop
			case 4: number = 0; break; //reset
			case 8: number--; break; //decrease
		}
		
		digits_get(&number, digits);
		digits_show();
		time = 10; //1 ms		
	}
	else
	time--;
	
}

int main(void)
{
	//exercise 4
	DDRC = 0xff; //segments A-DP
	DDRB = 0x0f; //choose 7seg display
	PORTA = 0x0f; //4 buttons, pull-up resistor
	
	TCCR0 |= (1<<WGM01) | (1<<CS01); //ctc mode, prescaler: 8
	TIMSK |= (1<<OCIE0); //compare output mode
	OCR0 = 99; //10 kHz = 100 us
	sei();
	
	while(1);
	return 0;
}