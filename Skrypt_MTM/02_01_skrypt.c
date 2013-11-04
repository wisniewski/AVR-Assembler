----------------------------------------------------------------------------------
2.1 / 1
----------------------------------------------------------------------------------

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

----------------------------------------------------------------------------------
2.1 / 2
----------------------------------------------------------------------------------

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

----------------------------------------------------------------------------------
2.1 / 4
----------------------------------------------------------------------------------

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

----------------------------------------------------------------------------------
2.1 / 5
----------------------------------------------------------------------------------

#include <avr/io.h>

int main(void)
{
	DDRA = 0xff; //255
	DDRA &= 0xab; //zeruje bity 2, 4 i 6 //zerowanie dzieki AND
	DDRA |= 0b01010100; //znowu ddra = 0xff / ustawianie dzieki OR
	DDRA ^= 0x01; //neguje najmlodszy bitu dzieki XOR

	return 0;
}

----------------------------------------------------------------------------------
2.1 / 6
----------------------------------------------------------------------------------

#include <avr/io.h>

int main(void)
{
	PORTA = 0x07; //0b00000111
	PORTB = 0x0f; //0b00001111
	PORTB |= (PORTA << 5);
	//

	return 0;
}
