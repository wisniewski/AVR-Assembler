/* Wykorzystanie Timera0 w trybie CTC oraz przerwan do wyswietlania tresci na
wyswietlaczu LCD przy wykorzystaniu jednego ciagu formatujacego zawierajacego
rowniez komendy (inicjalizujace go oraz sterujace) dla sterownika. 

Poprawiony kod: usuniecie delaya, poprawka definicji zmiennych

Zaczenie tworzenia menu dla LCD opartego na strukturach */

#include <avr/io.h> //I/O, rejestry itd.
#include <avr/pgmspace.h> //progmem
#include <stdlib.h> //malloc
#include <stdio.h> //sprintf
#include <avr/interrupt.h> //przerwania

struct lcd_field //definicja struktury
{
	volatile char rs : 1; //zmienna nie podlegajaca procesowi optymalizacji
	volatile char rw : 1;
	volatile char e : 1;
	volatile char : 1; //odstep bo trzeciego bitu nie uzywamy
	volatile char data : 4; //dostep do d4-d7 w LCD
};

#define lcd_rs ((*((struct lcd_field *) &PORTB)).rs) //0 lub 1 na pinie
#define lcd_rs_dir (((struct lcd_field *) &DDRB) -> rs)
//operator wyluskania pola -> jesli mamy wskaznik do struktury, INICJALIZACJA

#define lcd_rw ((*((struct lcd_field *) &PORTB)).rw) //0 lub 1 na pinie
#define lcd_rw_dir (((struct lcd_field *) &DDRB) -> rw) //inicjalizacja

#define lcd_e ((*((struct lcd_field *) &PORTB)).e) //0 lub 1 na pinie
#define lcd_e_dir (((struct lcd_field *) &DDRB) -> e) //inicjalizacja

#define lcd_data ((*((struct lcd_field *) &PORTD)).data) //0 lub 1 na pinie
#define lcd_data_dir (((struct lcd_field *) &DDRD) -> data) //inicjalizacja

//deklaracje uzytych funkcji
void lcd_initiation (char data, char rs);
void lcd_write_data(char data);
void lcd_write_command(char data);

/* - - - - - - - - - - - - menu - - - - - - - - - - - */

//struktura menu
struct menu
{
	struct menu *left;
	struct menu *right;
	struct menu *up;
	struct menu *down;
	char *str;
};

struct menu M1, M2, M3, M11, M12, M13, M131, M132, M21, M22, M31;

//definicja odwoluje sie do innych elementow {lewo, prawo, gora nic, dol, "string"}
struct menu M1 = {&M3, &M2, NULL, &M11, "M1"};
struct menu M2 = {&M1, &M3, NULL, &M21, "M2"};
struct menu M3 = {&M2, &M1, NULL, &M31, "M3"};

struct menu M11 = {&M13, &M12, &M1, NULL, "M11"};
struct menu M12 = {&M11, &M13, &M1, NULL, "M12"};
struct menu M13 = {&M12, &M11, &M1, &M131, "M13"};
struct menu M131 = {&M132, &M132, &M13, NULL, "M1311"};
struct menu M132 = {&M131, &M131, &M13, NULL, "M1312"};

struct menu M21 = {&M22, &M22, &M2, NULL, "M21"};
struct menu M22 = {&M21, &M21, &M2, NULL, "M22"};

struct menu M31 = {NULL, NULL, &M3, NULL, "M31"};

/* - - - - - - - - - - - - end menu - - - - - - - - - - - */

//komendy i tekst w jednym ciagu
const char lcd_format[] PROGMEM =
"\004\377\001\x28\004\377\001\x28\004\377\001\x28\004\377\
\001\x0c\004\377\001\x06\004\377\001\x01\004\377\1\x28\001\x81\
pies i krowa\004\377\001\x28\004\377\001\xc3Kot z umk";

//wait \004\377
//komenda \001\x28

volatile  uint8_t lcd_buff_full;
char *lcd_buff;

ISR(TIMER0_COMP_vect) //10 k Hz = 100 us
{
	static uint8_t lcd_cnt = 0, lcd_read = 0;
	
	if((lcd_buff_full) && (lcd_cnt == 0))
	{
		switch(lcd_buff[(int)lcd_read])
		{
			case 0: //koniec lancucha
			{
				lcd_buff_full = 0;
				lcd_read = 0;
			}
			break;
			case 1: //wyslanie komendy do wyswietlacza
			{
				lcd_read++;
				lcd_write_command(lcd_buff[lcd_read++]); //wysylam komende
				//i znowu inkrementuje, aby wskazywac na kolejny element
			}
			break;
			case 4: //czekanie
			{
				lcd_read++;
				lcd_cnt = lcd_buff[lcd_read++];
			}
			break;
			//lcd_read mowi ktory znak odczytac oraz inkrementacja do nastepnego znaku
			default: lcd_write_data(lcd_buff[lcd_read++]);
		}
	}
	else if(lcd_cnt > 0)
	{
		lcd_cnt--;
	}
}

int main (void)
{
	//inicjalizacja LCD
	lcd_rs_dir = 1;
	lcd_rw_dir = 1;
	lcd_e_dir = 1;
	lcd_data_dir = 0xf;

	lcd_buff_full = 1;
	lcd_buff = malloc(32);
	sprintf_P(lcd_buff, lcd_format);
	
	TCCR0 |= _BV(CS01) | (1 << WGM01);
	TIMSK |= (1 << OCIE0);
	OCR0 = 99;
	sei();
	
	while(1);
	
	return 0;
}

/* - - - - funkcje uzyte w mainie - - - - */

void lcd_initiation (char data, char rs)
{
	lcd_rw = 0;
	lcd_rs = rs;
	lcd_e = 1;
	lcd_data = data >> 4; //przesuniecie na 4 najmlodsze bity
	lcd_e = 0;
	lcd_e = 1;
	lcd_data = data & 0xF;
	lcd_e = 0;
	//gdyby nie pola bitowe... (((((PORTD >> 4)++) & 0xF) << 2) | PORTD & 0xC3)
}

void lcd_write_data(char data)
{
	lcd_initiation(data, 1); //1 bo RS 1 to data
}

void lcd_write_command(char data)
{
	lcd_initiation(data, 0); //0 to command
}