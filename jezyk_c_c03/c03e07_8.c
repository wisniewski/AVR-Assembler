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