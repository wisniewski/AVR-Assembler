/* Woltomierz zrezlizowany na Atmega32 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

const uint8_t led_digits[10] PROGMEM = {192, 249, 164, 176, 153, 146, 130, 248, 128, 144};

void timer0_init(void);
uint8_t keyboard_scan(void);
void led_show(uint16_t measurement);
uint16_t power(uint8_t base, uint8_t exp);
void adc_init(void);

ISR(TIMER0_COMP_vect)
{
	static uint16_t time;
	static uint8_t keyboard_number;
	float measurement = 0.0;

	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	
	measurement = ADC*5.0 / 1023.0;
	uint8_t num; uint16_t frac;
	num = (uint8_t) measurement;
	frac = (uint16_t) ((measurement - num) * 1000);

	led_show(num*1000+frac);
	
	if(!time)
	{
		time = 100;
		keyboard_number = keyboard_scan();
	}
	else
		time--;
}

int main(void)
{
	DDRB = 0x0f; //leds
	PORTB = 0x0f;
	DDRD = 0xff;
	PORTD = 0xff;
	DDRC = 0x0f; //keyboard
	PORTC = 0xff;

	timer0_init();
	adc_init();

	sei();

	while(1);
	return 0;
}

void led_show(uint16_t measurement)
{
	uint8_t static number;
	
	uint8_t digit[4] = {0};
	for(int i=0; i<4; i++)
		*(digit+i) = (measurement / power(10,i)) % 10;

	PORTB = (PORTB | 0x0f) & ~(1<<number);
	if(number == 3)
		PORTD = pgm_read_byte(&led_digits[*(digit+number++)]) & ~(0x80);
	else
		PORTD = pgm_read_byte(&led_digits[*(digit+number++)]);
	if(number>3)
		number = 0;

}

void timer0_init(void) 
{
	TCCR0 = (1<<WGM01) | (1<<CS01);
	OCR0 = 199;
	TIMSK = (1<<OCIE0);
}

uint8_t keyboard_scan(void)
{
	for(int row=0; row<4; row++)
	{
		PORTC = (PORTC | 0x0f) & ~(1<<row);
		asm volatile ("nop");

		for(int col=0; col<4; col++)
		{
			if((PINC & (0x10 << col)) == 0)
				return 1 + (4*row + col);
		}
	}
	return 0;
}

uint16_t power(uint8_t base, uint8_t exp)
{
	uint16_t val=1;
	while(exp)
	{
		val *= base;
		exp--;
	}
	return val;
	
}

void adc_init(void)
{
	ADMUX = (1<<REFS0);
	ADCSRA = (1<<ADEN) | (1<<ADPS0) | (1<<ADPS1)  | (1<<ADPS2);
}
