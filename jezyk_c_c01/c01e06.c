#include <avr/io.h>

int main(void)
{
	PORTA = 0x07; //0b00000111
	PORTB = 0x0f; //0b00001111
	PORTB |= (PORTA << 5);
	//

	return 0;
}