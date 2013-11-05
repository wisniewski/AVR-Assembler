----------------------------------------------------------------------------------
2.3 / 1
----------------------------------------------------------------------------------
#include<avr/io.h>

void increase_digit(uint8_t *i_P, uint8_t *actual_digit_P)
{
	*actual_digit_P = ((1 << *i_P) % 4) ; //kod 1 z 4
	(*i_P)++;
}

int main(void)
{
	uint8_t i = 0, actual_digit = 0;
	
	increase_digit(&i, &actual_digit);
	
	return 0;
}
----------------------------------------------------------------------------------
2.3 / 2
----------------------------------------------------------------------------------
#include<avr/io.h>

void select_digits_value(uint8_t digits_values_P[], uint16_t *number_P)
{
	*digits_values_P++ = (((*number_P/10)/10)/10) % 10;
	*digits_values_P++ = ((*number_P/10)/10) % 10;
	*digits_values_P++ = (*number_P/10) % 10;
	*digits_values_P = *number_P % 10;
}

void increase_digit(uint8_t *i_P, uint8_t *actual_digit_P)
{
	*actual_digit_P = ((1 << *i_P) % 4) ; //kod 1 z 4
	(*i_P)++;
}

int main(void)
{
	uint8_t digits_values[4] = {0};
	uint8_t i = 0, actual_digit = 0;
	uint16_t number = 1234;
	
	increase_digit(&i, &actual_digit);
	
	select_digits_value(digits_values, &number);
	
	return 0;
}
----------------------------------------------------------------------------------
2.3 / 3 + 5 + 6
----------------------------------------------------------------------------------
#include<avr/io.h>
#include<avr/pgmspace.h>

const uint8_t PROGMEM digits_show[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void select_digits_value(uint8_t digits_values_P[], uint16_t *number_P)
{
	*digits_values_P++ = (((*number_P/10)/10)/10) % 10;
	*digits_values_P++ = ((*number_P/10)/10) % 10;
	*digits_values_P++ = (*number_P/10) % 10;
	*digits_values_P = *number_P % 10;
}

void increase_digit(uint8_t *i_P, uint8_t *actual_digit_P)
{
	*actual_digit_P = ((1 << *i_P) % 4) ; //kod 1 z 4
	(*i_P)++;
}

int main(void)
{
	uint8_t digits_values[4] = {0};
	uint8_t i = 0, actual_digit = 0;
	uint16_t number = 1234;
	
	increase_digit(&i, &actual_digit);
	
	select_digits_value(digits_values, &number);
	
	return 0;
}
----------------------------------------------------------------------------------
2.3 / 4
----------------------------------------------------------------------------------
U mnie konfiuracja na płytce stykowej jest następująca:
uC: ATmega32A
Wyświetlacz 7-segmentowy: 4-cyfrowy ze wspólną katodą (cai5461ah 4 digit)
Tranzystory: NPN BC547B
PCx - rezystor - baza
PDx - rezystor - segment A itd.
----------------------------------------------------------------------------------
2.3 / 7 + 8
----------------------------------------------------------------------------------
#include<avr/io.h>
#include<avr/pgmspace.h>
#include<util/delay.h>

const uint8_t PROGMEM digits_show[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void select_digits_value(uint8_t digits_values_P[], uint16_t *number_P)
{
	*digits_values_P++ = (((*number_P/10)/10)/10) % 10;
	*digits_values_P++ = ((*number_P/10)/10) % 10;
	*digits_values_P++ = (*number_P/10) % 10;
	*digits_values_P = *number_P % 10;
}

uint8_t increase_digit(uint8_t *i_P, uint8_t *actual_digit_P)
{
	*actual_digit_P = (1 << *i_P) ; //kod 1 z 4
	*i_P = (*i_P + 1) % 4;
	return *actual_digit_P;
}

int main(void)
{
	//uint8_t digits_values[4] = {0};
	uint8_t i = 0, actual_digit = 0, inc = 0;
	//uint16_t number = 1234;
	
	DDRD = 0xff;
	DDRC = 0x0f;
	
	while(1)
	{
		PORTC = increase_digit(&i, &actual_digit);
		PORTD = pgm_read_byte(&digits_show[inc = (inc + 1) % 10]);
		_delay_ms(1000);
	}
	
	//increase_digit(&i, &actual_digit);
	//select_digits_value(digits_values, &number);
	
	return 0;
}
----------------------------------------------------------------------------------
2.3 / 8a (wykorzystanie wczesniejszych funkcji)
----------------------------------------------------------------------------------
#include<avr/io.h>
#include<avr/pgmspace.h>
#include<util/delay.h>

const uint8_t PROGMEM digits_show[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void select_digits_value(uint8_t digits_values_P[], uint16_t *number_P)
{
	*digits_values_P++ = (((*number_P/10)/10)/10) % 10;
	*digits_values_P++ = ((*number_P/10)/10) % 10;
	*digits_values_P++ = (*number_P/10) % 10;
	*digits_values_P = *number_P % 10;
}

uint8_t increase_digit(uint8_t *i_P, uint8_t *actual_digit_P)
{
	*actual_digit_P = (1 << *i_P) ; //kod 1 z 4
	*i_P = (*i_P + 1) % 4;
	return *actual_digit_P;
}

int main(void)
{
	uint8_t digits_values[4] = {0};
	uint8_t i = 0, actual_digit = 0, inc = 0;
	uint16_t number = 6;
	
	DDRD = 0xff;
	DDRC = 0x0f;
	
	while(1)
	{
		select_digits_value(digits_values, &number);
		PORTC = increase_digit(&i, &actual_digit);
		PORTD = pgm_read_byte(&digits_show[digits_values[inc++]]);
		inc %= 4;
		_delay_ms(1);
	}
	
	return 0;
}
----------------------------------------------------------------------------------
2.3 / 8b (wykorzystanie przerwan)
----------------------------------------------------------------------------------
#include<avr/io.h>
#include<avr/pgmspace.h>
#include<avr/interrupt.h>

const uint8_t PROGMEM digits_show[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void select_digits_value(uint8_t digits_values_P[], uint16_t *number_P)
{
	*digits_values_P++ = (((*number_P/10)/10)/10) % 10;
	*digits_values_P++ = ((*number_P/10)/10) % 10;
	*digits_values_P++ = (*number_P/10) % 10;
	*digits_values_P = *number_P % 10;
}

uint8_t increase_digit(uint8_t *i_P, uint8_t *actual_digit_P)
{
	*actual_digit_P = (1 << *i_P) ; //kod 1 z 4
	*i_P = (*i_P + 1) % 4;
	return *actual_digit_P;
}

ISR(TIMER0_COMP_vect) //10kHz - 100us
{
	uint8_t digits_values[4] = {0};
	uint8_t static i = 0, actual_digit = 0, inc = 0;
	uint16_t number = 9874;
	select_digits_value(digits_values, &number);
	PORTC = increase_digit(&i, &actual_digit);
	PORTD = pgm_read_byte(&digits_show[digits_values[inc++]]);
	inc %= 4;
}

int main(void)
{
	DDRD = 0xff;
	DDRC = 0x0f;
	
	TCCR0 |= _BV(CS01) | (1 << WGM01);
	TIMSK |= (1 << OCIE0);
	OCR0 = 99;
	sei();
	while(1);
	
	return 0;
}
----------------------------------------------------------------------------------
2.3 / 9 (bez przerwan)
----------------------------------------------------------------------------------
#include<avr/io.h>
#include<avr/pgmspace.h>
#include<util/delay.h>

const uint8_t PROGMEM digits_show[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void select_digits_value(uint8_t digits_values_P[], uint16_t *number_P)
{
	*digits_values_P++ = (((*number_P/10)/10)/10) % 10;
	*digits_values_P++ = ((*number_P/10)/10) % 10;
	*digits_values_P++ = (*number_P/10) % 10;
	*digits_values_P = *number_P % 10;
}

uint8_t increase_digit(uint8_t *i_P, uint8_t *actual_digit_P)
{
	*actual_digit_P = (1 << *i_P) ; //kod 1 z 4
	*i_P = (*i_P + 1) % 4;
	return *actual_digit_P;
}

int main(void)
{
	uint8_t digits_values[4] = {0};
	uint8_t i = 0, actual_digit = 0, inc = 0;
	uint16_t number = 1;
	
	DDRD = 0xff;
	DDRC = 0x0f;
	
	while(1)
	{
		select_digits_value(digits_values, &number);
		PORTC = increase_digit(&i, &actual_digit);
		PORTD = pgm_read_byte(&digits_show[digits_values[inc++]]);
		inc %= 4;
		number = (number + 1) % 10000;
		_delay_ms(1);
	}
	
	return 0;
}
----------------------------------------------------------------------------------
2.3 / 10 - brak debouncingu
----------------------------------------------------------------------------------
/*przycisk na PB0, pull-up do wew. rezystora*/

#include<avr/io.h>
#include<avr/pgmspace.h>
#include<util/delay.h>

const uint8_t PROGMEM digits_show[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void select_digits_value(uint8_t digits_values_P[], uint16_t *number_P)
{
	*digits_values_P++ = (((*number_P/10)/10)/10) % 10;
	*digits_values_P++ = ((*number_P/10)/10) % 10;
	*digits_values_P++ = (*number_P/10) % 10;
	*digits_values_P = *number_P % 10;
}

uint8_t increase_digit(uint8_t *i_P, uint8_t *actual_digit_P)
{
	*actual_digit_P = (1 << *i_P) ; //kod 1 z 4
	*i_P = (*i_P + 1) % 4;
	return *actual_digit_P;
}

int main(void)
{
	uint8_t digits_values[4] = {0};
	uint8_t i = 0, actual_digit = 0, inc = 0, button[2];
	uint16_t number = 1;
	
	PORTB = _BV(PB0);
	DDRD = 0xff;
	DDRC = 0x0f;
	button[1] = 0;
	while(1)
	{
		button[0] = PINB & 0x01;
		select_digits_value(digits_values, &number);
		PORTC = increase_digit(&i, &actual_digit);
		PORTD = pgm_read_byte(&digits_show[digits_values[inc++]]);
		inc %= 4;
		
		if(button[0] == 0)
			button[1] = 1 - button[1];
		if(button[1])
			{
				number++;
				_delay_ms(1);
			}
	}
	
	return 0;
}
----------------------------------------------------------------------------------
2.3 / 11 - jako-taki debouncing
----------------------------------------------------------------------------------
/* przyciski PB0 - PB2 */
#include<avr/io.h>
#include<avr/pgmspace.h>
#include<util/delay.h>

const uint8_t PROGMEM digits_show[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void select_digits_value(uint8_t digits_values_P[], uint16_t *number_P)
{
	*digits_values_P++ = (((*number_P/10)/10)/10) % 10;
	*digits_values_P++ = ((*number_P/10)/10) % 10;
	*digits_values_P++ = (*number_P/10) % 10;
	*digits_values_P = *number_P % 10;
}

uint8_t increase_digit(uint8_t *i_P, uint8_t *actual_digit_P)
{
	*actual_digit_P = (1 << *i_P) ; //kod 1 z 4
	*i_P = (*i_P + 1) % 4;
	return *actual_digit_P;
}

int main(void)
{
	uint8_t digits_values[4] = {0};
	uint8_t i = 0, actual_digit = 0, inc = 0, button[4];
	int8_t j=1;
	uint16_t number = 1, time = 0;
	
	PORTB = _BV(PB0) | _BV(PB1) | _BV(PB2);
	DDRD = 0xff;
	DDRC = 0x0f;
	button[0] = 0;
	while(1)
	{
		button[1] = PINB & _BV(PB0);
		button[2] = PINB & _BV(PB1);
		button[3] = PINB & _BV(PB2);
		select_digits_value(digits_values, &number);
		PORTC = increase_digit(&i, &actual_digit);
		PORTD = pgm_read_byte(&digits_show[digits_values[inc++]]);
		inc %= 4;
		if(time == 0)
		{
			if(!button[1])
			{
				number = 0; 
				time = 100;}
			else if(!button[2])
			{
				j = -j;
				time = 100;
				}
			else if(button[3] == 0)
			{
				button[0] = 1 - button[0];
				time = 100;
				}
			if(button[0])
			{
				number += j;
				_delay_ms(1);
			}
		}
		else
		{
			time--;
			_delay_ms(1);
		}
		
	}
	
	return 0;
}
