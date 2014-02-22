/* Kalkulator na klawiaturze matrycowej 4x4, liczby od 0 do 9, +, -, *, /, reset, =
To jest moja propozycja rozwi¹zania, aczkolwiek idea jak i sposob
dzialania jest identyczny niczym z kodem od Chaberskiego*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>

const uint8_t digits_segment[10] PROGMEM = {192, 249, 164, 176, 153, 146, 130, 248, 128, 144};
uint8_t digits[4]={0};

uint16_t power(uint16_t base, uint8_t exp)
{
	if(!exp)
	return 1;
	else if(exp)
	return base * power(base, exp-1);
	
	return 0;
}

void digits_get(uint8_t *num, uint8_t tab[])
{
	for(uint8_t i = 0; i<4; i++)
	{
		*tab++ = (*num / power(10, i)) % 10;
	}
}

void digits_show(void)
{
	static uint8_t i;
	PORTB = 0xff;
	PORTB = 0x0f ^ (1<<(++i%4));
	PORTC = pgm_read_byte(&digits_segment[digits[i%4]]);
}

uint8_t button_read(void)
{
	for(uint8_t row = 0; row<4; row++)
	{
		ATOMIC_BLOCK(ATOMIC_FORCEON) //do not use cli/sei !!!
		{
			PORTA = (PORTA | 0x0f) ^ (1<<row);
		}
		for(uint8_t col = 0; col<4; col++)
		{
			if((PINA & (0x10 << col)) == 0)
			return (4*row + col);
		}
	}
	return 16;
}

ISR(TIMER0_COMP_vect)
{
	static uint8_t number, button_time, time, number_get=16;
	static uint8_t status=0, operation[3], result; 
	
	if(!time)
	{
		if(!button_time)
		{
			number = button_read();
			if(number < 16)
			{
				number_get = number;
			}
			button_time = 200;
		}
		else
		button_time--;
		
		if(number_get == 14) //reset
		{
			status = 0;
			for(int j=0; j<3; j++)
			operation[j]=0;
			result = 0;
		}
		
		switch(status)
		{
			case 0: //get first number
			{
				if((number_get >= 0) && (number_get < 10))
				{
					operation[0] = number_get;
					status = (status+1) % 4;
				}
			}
			break;
			case 1: //get operator
			{
				if((number_get >= 10) && (number_get < 14))
				{operation[1] = number_get;status = (status+1) % 4;}
			}
			break;
			case 2: //get second number
			{
				if((number_get >= 0) && (number_get < 10))
				{operation[2] = number_get;status = (status+1) % 4;}
			}
			break;
			case 3: //get result, equal operator
			{
				if(number_get == 15)
				{
					switch(operation[1]) //add, divide etc.
					{
						case 10:
						result = operation[0]+operation[2];
						break;
						
						case 11:
						result = operation[0]-operation[2];
						break;
						
						case 12:
						result = operation[0]*operation[2];
						break;
						
						case 13:
						result = operation[0]/operation[2];
						break;
					}
					status = (status+1) % 4;
				}
			}
			break;
		}

		if(status!=0) //show only choosen number
		if(number_get<10)
		digits_get(&number_get, digits);
		if(status==0) //show only result
		digits_get(&result, digits);
		
		digits_show();
		PORTD = 1 << status;	//sygnalize where i am	
		time = 10; //1 ms
	}
	else
	time--;
}

int main(void)
{
	DDRC = 0xff; //segments A-DP
	DDRB = 0x0f; //choose 7seg display
	DDRA = 0x0f; //output LSB in matrix
	PORTA = 0xf0; //pull-up resistor for MSB, input
	DDRD = 0x0f; //show status on 4 leds
	
	TCCR0 |= (1<<WGM01) | (1<<CS01); //ctc mode, prescaler: 8
	TIMSK |= (1<<OCIE0); //compare output mode
	OCR0 = 99; //10 kHz = 100 us
	sei();
	
	while(1);
	return 0;
}