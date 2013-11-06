#include <avr/io.h>

int main(void)
{
	DDRA = 0xff; //jako wyjscie
	DDRB = 0x00; //jako wejscie 
	PORTB = 0xff; //pull-up (podciagniecie pod wew. rezystor / VCC)
	
    while(1)
    { 
		PORTA = PINB; //stan na wyjsciu PA bedzie odpowiadal stanowu na wejsciu PB 
    }
	return 0;
}