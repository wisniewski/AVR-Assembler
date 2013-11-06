#include <avr/io.h>
#include <util/delay.h> //opoznienia

int main(void)
{
	DDRA = 0xff; //jako wyjscie
	DDRB = 0x00; //jako wejscie 
	PORTB = 0xff; //pull-up (podciagniecie pod wew. rezystor / VCC)
	
    while(1)
    { 
		PORTA++; //zwiekszamy od 0 do 255 - ustawianie stanow
		_delay_ms(1000); //odczekaj sekunde
    }
	return 0;
}