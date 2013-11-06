#include <avr/io.h>
#include <util/delay.h> //opoznienia

int main(void)
{
	DDRA = 0xff; //jako wyjscie
	DDRB = 0x00; //jako wejscie 
	PORTB = 0xff; //pull-up (podciagniecie pod wew. rezystor / VCC)
	asm volatile ("nop"); //synchronizator
    while(1)
    { 
		if((PINB & _BV(PB0)) == 0) //jesli nacisniemy przycisk na PB0
		//lub if(!(PINB & 0x01))
		{
			PORTA++; //zwiekszamy od 0 do 255 - ustawianie stanow
		}
		else
		{
			PORTA--;
		}	
		//_delay_ms(1000); //odczekaj sekunde
    }
	return 0;
}