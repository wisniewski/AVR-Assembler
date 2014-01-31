/* Read matrix keyboard, show number on multiplexing 7-digit displays
* uC: ATmega32
* Settings: 
* - matrix keyboard: PC0...PC7
* - select 7segment display: PD0..PD3
* - 7segment digit: PA0...PA7
*
* Mariusz Wisniewski
* 254019
* AiR
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

const uint8_t show_digits[10] PROGMEM = {192, 249, 164, 176, 153, 146, 130, 248, 128, 144};

uint8_t read_button(void)
{
	uint8_t row, col;
	for(row=0; row<4; row++) //check matrix keyboard
	{
		PORTC = (PORTC | 0x0f) ^ (1<<row); //choose row
		for(col=0; col<4; col++)
		{
			if(!(PINC & (0x10 << col))) //check each column one by one
			return 1 + (4*row + col); //send number
		}
	}
	return 0; //if nothing pressed
}

ISR(TIMER0_COMP_vect)
{
	static uint16_t time;
	static uint8_t i, j;
	uint16_t number = read_button(); 

	uint8_t number_digit[4]; //get each digit
	number_digit[0]= number % 10;
	number_digit[1]= (number/10) % 10;
	number_digit[2]= (number/100) % 10;
	number_digit[3]= (number/1000) % 10;

	if(!time)
	{
		PORTD = (1<<(++i)%4) ^ 0x0f; //select display
		PORTA = pgm_read_byte(&show_digits[number_digit[(++j)%4]]); //show digit
		time = 10; //1 ms
	}
	else if(time)
	time--;
}

int main(void)
{
	DDRD = 0xff; //select segment
	DDRA = 0xff; //show digit
	
	DDRC = 0x0f; //LSB output
	PORTC = 0xf0; //MSB pull up, input

	TCCR0 |= (1<<WGM01) | (1<<CS01); //ctc mode, prescaler: 8
	TIMSK |= (1<<OCIE0); //compare output mode
	OCR0 = 99; //10 kHz = 100 us
	sei();

	while(1);
	return 0;
}
