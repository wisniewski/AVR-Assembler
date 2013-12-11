/* Woltomierz zrezlizowany na Atmega32A na wejsciu PA7 przetwornika
cyfrowo - analogowego (ADC). Po wykonaniu pomiaru jest generowane 
przerwanie. Aktualizacja cyfr na multipleksowanym wyswietlaczu 
7 segmentowym ze wspolna katoda jest w przerwaniu Timera0 w trybie CTC.
*/

#include<avr/io.h>
#include<avr/pgmspace.h>
#include<avr/interrupt.h>
#include<stdint.h>

const uint8_t PROGMEM digits_show[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
0x6D, 0x7D, 0x07, 0x7F, 0x6F};

uint8_t measurement = 0;

//deklaracja uzytyvh funkcji
void select_digits_value(uint8_t [], uint8_t *);
uint8_t increase_digit(uint8_t *, uint8_t *);

ISR(ADC_vect)
{
	//odczyt wartosci
	float temp;
	temp = (ADC*5.0f)/1023.0f*10.0f;
	measurement = (uint8_t) temp; //konwersja z float na uint8_t
}

//obsluga timera0 w trybie CTC
ISR(TIMER0_COMP_vect) //1kHz = 1 milisekunda
{
	uint8_t digits_values[2] = {0}; //tablica od cyfr
	uint8_t static i = 0, actual_digit = 0, inc = 0;
	select_digits_value(digits_values, &measurement);
	PORTC = increase_digit(&i, &actual_digit);
	
	//przecinek dziesietny tylko po pierwszej cyfrze
	if(!inc)
		PORTD = pgm_read_byte(&digits_show[digits_values[inc++]]) | 0x80; //DP 7seg
	else 
		PORTD = pgm_read_byte(&digits_show[digits_values[inc++]]); //bez DP 7seg
	inc %= 2;
	
}

int main(void)
{
	DDRD = 0xff; //do sterowania segmentami
	DDRC = 0x03; //do sterowania tranzystorami
	
	//konfiguracja timera0 w trybie CTC 1kHz, czyli do uzyskania liczba 8k
	TCCR0 |= _BV(CS01) | _BV(CS00) | (1 << WGM01);
	TIMSK |= (1 << OCIE0);
	OCR0 = 124; //8000 = 64*124+1
	
	//konfiguracja ADC w trybie konwersji ciaglej z przerwaniem
	ADMUX = _BV(REFS0) | _BV(MUX0) |  _BV(MUX1) |  _BV(MUX2);
	//Vref = Vcc, PA7
	ADCSRA = _BV(ADEN) | _BV(ADIE)  | _BV(ADATE) | _BV(ADSC) | _BV(ADPS2);
	//preskaler 64, wlaczenie ADC, przerwan
	
	sei(); //wlaczenie przerwan
	while(1); //nieskonczona petla
	return 0;
}

//wpisanie do tablicy poszczegolnej cyfry (dziesiatka i jednosc)
void select_digits_value(uint8_t digits_values[], uint8_t *num)
{
	*digits_values++ = (*num/10) % 10;
	*digits_values = *num % 10;
}

//kod 1 z n, wyswietlaj najpierw 1 cyfre, potem druga
uint8_t increase_digit(uint8_t *i, uint8_t *actual_digit)
{
	*actual_digit = (1 << *i) ; //kod 1 z 2
	*i = (*i + 1) % 2;
	return *actual_digit;
}