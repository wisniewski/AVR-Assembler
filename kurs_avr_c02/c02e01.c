----------------------------------------------------------------------------------
1
----------------------------------------------------------------------------------
#include <avr/io.h>
 
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
//operator wyluskania pola -> jesli mamy wskaznik do struktury, INIZJALIZACJA
 
#define lcd_rw ((*((struct lcd_field *) &PORTB)).rw) //0 lub 1 na pinie
#define lcd_rw_dir (((struct lcd_field *) &DDRB) -> rw) //inicjalizacja
 
#define lcd_e ((*((struct lcd_field *) &PORTB)).e) //0 lub 1 na pinie
#define lcd_e_dir (((struct lcd_field *) &DDRB) -> e) //inicjalizacja
 
#define lcd_data ((*((struct lcd_field *) &PORTD)).data) //0 lub 1 na pinie
#define lcd_data_dir (((struct lcd_field *) &DDRD) -> data) //inicjalizacja
 
/*  - -  - - funkcje  - -  - - */
 
void lcd_write (char data, char rs)
{
    lcd_rw = 0;
    lcd_rs = rs;
    lcd_e = 1;
    lcd_data = data >> 4; //przesuniecie o 4 bity w prawo
    lcd_e = 0;
    lcd_e = 1;
    lcd_data = data & 0xF;
    lcd_e = 0;
    //gdyby nie pola bitowe, powstawaly by konstrukcje podobnego typu:
    // (((((PORTD >> 4)++) & 0xF) << 4) | PORTD & 0xC3)
}
 
void lcd_DATA(char data)
{
    lcd_write(data, 1); //1 bo RS 1 to data
}
 
void lcd_COMMAND(char data)
{
    lcd_write(data, 0); //0 to command
}
 
int main (void)
{
    //testowanie poprawnosci funkcji na diodach LED
    lcd_rs_dir = 1;
    lcd_rw_dir = 1;
    lcd_e_dir = 1;
    lcd_data_dir = 0xf;
 
    lcd_DATA(0x01);
 
    return 0;
}
