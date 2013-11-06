/*przycisk na PB0, pull-up do wew. rezystora
brak debouncingu*/

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