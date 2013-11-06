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