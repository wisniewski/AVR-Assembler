/* Wyswietlanie na wyswietlaczu 7segmentowym danych pobieranych do ADC z potencjometru,
2 tryby - wyswietlanie wyniku oraz aktualnej konwersji ADC, 4 przyciski:
przelacz tryb, dodaj do wyniku ADC, odejmij i reset */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

const uint8_t digits_segment[10] PROGMEM = {192, 249, 164, 176, 153, 146, 130, 248, 128, 144};
uint8_t digits[4]={0};
uint8_t mode;

uint16_t sounds[50];

uint16_t power(uint16_t base, uint8_t exp)
{
	if(!exp)
	return 1;
	else if(exp)
	return base * power(base, exp-1);
	
	return 0;
}

void digits_get(uint16_t num, uint8_t tab[])
{
	for(uint8_t i = 0; i<4; i++)
	{
		*tab++ = (num / power(10, i)) % 10;
	}
}

void digits_show(void)
{
	static uint8_t i;
	PORTB = 0xff;
	PORTB = 0x0f ^ (1<<(++i%4));
	PORTC = pgm_read_byte(&digits_segment[digits[i%4]]);
}

void sound_play()
{

	if(ADC < 256)
	TCCR2 |= _BV(WGM20) | _BV(WGM21) | _BV(COM21) | _BV(COM20) | _BV(CS21); //8
	else if(ADC < 512)
	TCCR2 |= _BV(WGM20) | _BV(WGM21) | _BV(COM21) | _BV(COM20) | _BV(CS21) | _BV(CS20); //32
	else if(ADC < 768)
	TCCR2 |= _BV(WGM20) | _BV(WGM21) | _BV(COM21) | _BV(COM20) | _BV(CS22); //64
	else
	TCCR2 |= _BV(WGM20) | _BV(WGM21) | _BV(COM21) | _BV(COM20) | _BV(CS22) | _BV(CS20); //128
	
}

void sound_play2(uint16_t j)
{
	if(j < 256)
	TCCR2 = 0x7a; //8
	else if(j < 512)
	TCCR2 = 0x7b; //32
	else if(j < 768)
	TCCR2 = 0x7c; //64
	else
	TCCR2 = 0x7d; //128
}

uint8_t button_read(void) //read 4 buttons, debouncing
{
	static uint8_t key_tmp, key_cnt, c;
	
	if(!key_cnt)
	{
		switch(c)
		{
			case 0:
			{
				key_tmp = PIND & 0x0f;
				if(key_tmp != 0x0f)
				{
					key_cnt = 10;
					c = 1;
				}
			}
			break;
			
			case 1:
			{
				if((PIND & 0x0f) == key_tmp)
				{
					c = 2;
					return (~key_tmp) & 0x0f;
				}
				else
				return 255;
			}
			break;
			
			case 2:
			{
				if((PIND & 0x0f) == 0x0f)
				c = 0;
			}
			break;
		}
	}
	else if(key_cnt>0)
	key_cnt--;
	
	return 255;
}

void menu(uint8_t button) //choose mode, add, minus, reset
{
	static uint8_t i;
	switch(button)
	{
		case 1:
		{
			mode ^= 1;
			if(mode)
			sound_play();
			else TCCR2 = 0;
		}
		break;
		
		case 2:
		{
			if(i<50)
			sounds[i++]=ADC;
			else
			i = 0;
		}
		break;
		
		case 4:
		{
			mode = (i > 0 ? 1 : 0);
			
			if(mode)
			{
				digits_get(i--, digits);
				sound_play2(sounds[i]);
			}
			else TCCR2 = 0;
			
		}
		break;
		case 8:
		{
			for(int j=0; j<=i; j++)
			sounds[j]=0;
			i = 0;
		}
		break;
	}
	digits_get(i, digits);
}

ISR(TIMER0_COMP_vect)
{
	static uint8_t time;
	uint8_t key;
	
	if(!time)
	{
		digits_show();
		key = button_read();
		if(key != 255)
		{
			menu(key);
		}
		time = 10; //1 ms
	}
	else
	time--;
}

ISR(ADC_vect) //get and show ADC measurement
{
	if(!mode)
	digits_get(ADC, digits);
}

int main(void)
{
	DDRC = 0xff; //segments A-DP
	DDRB = 0x0f; //choose 7seg display
	PORTD = 0x0f; //4 buttons, pul-up
	DDRD |= (1<<7); //pwm
	
	TCCR0 |= (1<<WGM01) | (1<<CS01); //ctc mode, prescaler: 8
	TIMSK |= (1<<OCIE0); //compare output mode
	OCR0 = 99; //10 kHz = 100 us
	
	ADMUX = 0x40; //enable ADC
	ADCSRA = 0xef;
	
	OCR2 = 128; //50% pwm
	
	sei();
	while(1);
	return 0;
}