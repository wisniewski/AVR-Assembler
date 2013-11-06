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