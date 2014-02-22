/* Dodawanie cyfr z klawiatury matrycowej, liczby od 1 do 16 
To jest moja propozycja rozwi¹zania, aczkolwiek idea jak i sposob
dzialania jest identyczny niczym z kodem od Chaberskiego*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>

const uint8_t digits_segment[10] PROGMEM = {192, 249, 164, 176, 153, 146, 130, 248, 128, 144};
uint8_t digits[4]={0};

uint16_t power(uint16_t base, uint8_t exp)
{
	if(!exp)
	return 1;
	else if(exp)
	return base * power(base, exp-1);
	
	return 0;
}

void digits_get(uint16_t *num, uint8_t tab[])
{
	for(uint8_t i = 0; i<4; i++)
	{
		*tab++ = (*num / power(10, i)) % 10;
	}
}

void digits_show(void)
{
	static uint8_t i;
	PORTB = 0xff;
	PORTB = 0x0f ^ (1<<(++i%4));
	PORTC = pgm_read_byte(&digits_segment[digits[i%4]]);
}

uint8_t button_read(void)
{
	for(uint8_t row = 0; row<4; row++)
	{
		ATOMIC_BLOCK(ATOMIC_FORCEON) //do not use cli/sei !!!
		{
			PORTA = (PORTA | 0x0f) ^ (1<<row);
		}
		for(uint8_t col = 0; col<4; col++)
		{
			if((PINA & (0x10 << col)) == 0)
			return 1 + (4*row + col);
		}
	}
	return 0;
}

ISR(TIMER0_COMP_vect)
{
	static uint16_t number, button_time;
	static uint8_t time;
	
	if(!time)
	{
		if(!button_time)
		{
			number += button_read();
			button_time = 100;
		}
		else
		button_time--;
		
		digits_get(&number, digits);
		digits_show();
		time = 10; //1 ms
	}
	else
	time--;
	
}

int main(void)
{
	DDRC = 0xff; //segments A-DP
	DDRB = 0x0f; //choose 7seg display
	DDRA = 0x0f; //output LSB in matrix
	PORTA = 0xf0; //pull-up resistor for MSB, input
	
	TCCR0 |= (1<<WGM01) | (1<<CS01); //ctc mode, prescaler: 8
	TIMSK |= (1<<OCIE0); //compare output mode
	OCR0 = 99; //10 kHz = 100 us
	sei();
	
	while(1);
	return 0;
}