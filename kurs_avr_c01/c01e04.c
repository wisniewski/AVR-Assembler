#include <avr/io.h>
 
//definicja struktury (pola bitowego)
struct bit_field
{
    volatile char b0 : 1; //zmienna nie podlegajaca procesowi optymalizacji
    volatile char b1 : 1; //1 bit
    volatile char b2 : 1;
    volatile char b3 : 1;
    volatile char b4 : 1;
    volatile char b5 : 1;
    volatile char b6 : 1;
    volatile char b7 : 1;
};
 
//wykorzystanie rzutowania - dwa rozne zapisy, identyczne dzialanie
#define DDR_LED3 ((*((struct bit_field *) &DDRA)).b3)
#define PORT_LED3 (((struct bit_field *) &PORTA) -> b3)
 
int main(void)
{
    DDR_LED3 = 1; //_BV(PA3)
    PORT_LED3 = 1;
 
    return 0;
}