/* Wykorzystanie Timera0 w trybie CTC oraz przerwań do wyświetlania treści na 
wyświetlaczu LCD przy wykorzystaniu jednego ciągu formatującego zawierającego 
również komendy dla sterownika. */

#include <avr/io.h> //I/O, rejestry itd.
#include <avr/pgmspace.h> //progmem
#include <stdlib.h> //malloc
#include <stdio.h> //sprintf
#include <util/delay.h> //opoznienia do inicjalizacji lcd
#include <avr/interrupt.h> //przerwania
 
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
 
const char lcd_format[] PROGMEM =
"\1\x28\001\x81Kocurkolandia!\001\xc3Szatan 666\001\x28\004\377";
 
ISR(TIMER0_COMP_vect) //10 k Hz = 100 us
{    
    char *lcd_buff = malloc(32);
    sprintf_P(lcd_buff, lcd_format);
    static uint8_t lcd_cnt = 0, lcd_read = 0, lcd_buff_full = 1;
 
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
    lcd_write_command(0x28); //fcn set, 4 bit, 8 lines
    _delay_ms(5);
    lcd_write_command(0x28); //fcn set, 4 bit, 8 lines
    _delay_ms(5);
    lcd_write_command(0x28); //fcn set, 4 bit, 8 lines
    _delay_ms(5);
 
    //konfigurowanie LCD
    lcd_write_command(0x0c); //display on
    _delay_ms(5);
    lcd_write_command(0x06); //entry mode on
    _delay_ms(5);
    lcd_write_command(0x01); //clear display
    _delay_ms(5);
 
    TCCR0 |= _BV(CS01) | (1 << WGM01);
    TIMSK |= (1 << OCIE0);
    OCR0 = 99;
    sei();
 
    while(1);
 
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
