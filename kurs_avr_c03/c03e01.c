----------------------------------------------------------------------------------
1
----------------------------------------------------------------------------------
#include <avr/io.h> //I/O, rejestry itd.
#include <util/delay.h> //opoznienie
#include <avr/pgmspace.h> //progmem
#include <stdlib.h> //malloc
#include <stdio.h> //sprintf
 
struct lcd_field //definicja struktury
{
    volatile char rs : 1; //zmienna nie podlegajaca procesowi optymalizacji
    volatile char rw : 1;
    volatile char e : 1;
    volatile char : 1; //odstep bo trzeciego bitu nie uzywamy
    volatile char data : 4; //dostep do d4-d7 w LCD
};
 
#define lcd_rs ((*((struct lcd_field *) &PORTC)).rs) //0 lub 1 na pinie
#define lcd_rs_dir (((struct lcd_field *) &DDRC) -> rs)
//operator wyluskania pola -> jesli mamy wskaznik do struktury, INICJALIZACJA
 
#define lcd_rw ((*((struct lcd_field *) &PORTC)).rw) //0 lub 1 na pinie
#define lcd_rw_dir (((struct lcd_field *) &DDRC) -> rw) //inicjalizacja
 
#define lcd_e ((*((struct lcd_field *) &PORTC)).e) //0 lub 1 na pinie
#define lcd_e_dir (((struct lcd_field *) &DDRC) -> e) //inicjalizacja
 
#define lcd_data ((*((struct lcd_field *) &PORTD)).data) //0 lub 1 na pinie
#define lcd_data_dir (((struct lcd_field *) &DDRD) -> data) //inicjalizacja
 
//deklaracje uzytych funkcji
void lcd_initiation (char data, char rs);
void lcd_write_data(char data);
void lcd_write_command(char data);
 
const char lcd_format[] PROGMEM = "liczba = %3.3u"; //umieszczenie w pamieci FLASH
const char lcd_format2[] PROGMEM = "Kocurkolandia!";
 
int main (void)
{
    //inicjalizacja LCD
    lcd_rs_dir = 1;
    lcd_rw_dir = 1;
    lcd_e_dir = 1;
    lcd_data_dir = 0xf;
 
    //konfigurowanie LCD
    lcd_write_command(0x28); //fcn set, 4 bit, 8 lines
    _delay_ms(5);
    lcd_write_command(0x0c); //display on
    _delay_ms(5);
    lcd_write_command(0x06); //entry mode on
    _delay_ms(5);
    lcd_write_command(0x01); //clear display
    _delay_ms(5);
 
    uint8_t i = 0, k = 0;
 
    char *lcd_message = malloc(80); //zaalokowanie pamieci
 
    while(1)
    {
        lcd_write_command(0xc2); //przeniesienie do 2 linii, drugie miejsce
        _delay_ms(5);
        uint8_t space = sprintf_P(lcd_message, lcd_format, k); //formatowanie
        //zapisuje ilosc zajetego miejsca w zmiennej space
        k++;
 
        while(lcd_message[i] != 0) //wypisywanie na ekran napisu
        {
 
            lcd_write_data(lcd_message[i++]);
            _delay_ms(1);
        }
 
        i = 0;
 
        lcd_write_command(0x81); //przeniesienie do 1 linii, pierwsze miejsce
        _delay_ms(5);
 
        sprintf_P(lcd_message + space, lcd_format2); //formatowanie
        //wskazuje do pierwszego pustego miejsca po zajetym napisie w formacie1
        i += space; //teraz i wskazuje na pierwsze wolne miejsce po formacie1
        while(lcd_message[i] != 0) //wypisywanie na ekran napisu
        {
 
            lcd_write_data(lcd_message[i++]);
            _delay_ms(1);
        }
 
        i = 0;
 
        _delay_ms(1000); //odliczanie do sekunde
        lcd_write_command(0x01); //czyszczenie wyswietlacza
        _delay_ms(5);
 
        _delay_ms(5);
    }
 
    return 0;
}
 
/*  - -  - - funkcje uzyte w mainie - -  - - */
 
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
