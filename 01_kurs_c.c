----------------------------------------------------------------------------------
1
----------------------------------------------------------------------------------
#include <stdlib.h> //obsluga malloca
 
int main(void)
{
    char *lcd; //deklaracja wskaznika do miejsca
    lcd = malloc(80); //rezerwuje miejsce w SRAM i przypisuje do lcd adres poczatkowy obszaru
    int i = 0; //zmienna do wypisywania w symulatorze
 
    while(1)
    {
        sprintf(lcd, "ABCD%2d", i); //wykorzystujemy sprintf do formatowania
        i++; //inkrementacja
    }
    return 0;
}
----------------------------------------------------------------------------------
2
----------------------------------------------------------------------------------
#include <stdio.h> //obsluga sprintf
#include <stdlib.h> //obsluga malloca
#include <avr/pgmspace.h> //progmem
 
const char format[] PROGMEM = "1234%03d";
//definicja formatu w pamieci FLASH
 
int main(void)
{
    char *lcd; //deklaracja wskaznika do miejsca
    lcd = malloc(80); //rezerwuje miejsce w SRAM i przypisuje do lcd adres poczatkowy obszaru
    int i = 0; //zmienna do wypisywania w symulatorze
 
    while(1)
    {
        sprintf_P(lcd,format,i); //wykorzystujemy sprintf do formatowania
        i++; //inkrementacja
    }
    return 0;
}
----------------------------------------------------------------------------------
3
----------------------------------------------------------------------------------
#include <stdio.h> //obsluga sprintf
#include <stdlib.h> //obsluga malloca
#include <avr/pgmspace.h> //progmem
 
const char format_1[] PROGMEM = "1234";
const char format_2[] PROGMEM = "%3d";
//definicja formatow w pamieci FLASH
 
int main(void)
{
    char *lcd; //deklaracja wskaznika do miejsca
    lcd = malloc(80); //rezerwuje miejsce w SRAM i przypisuje do lcd adres poczatkowy obszaru
    int i = 0; //zmienna do wypisywania w symulatorze
 
    //n przyjmie 4, czyli sprintf zwraca ilosc zajetych bajtow
    uint8_t n = sprintf_P(lcd,format_1); //wykorzystujemy sprintf_p do formatowania
 
    while(1)
    {
        sprintf_P(lcd+n, format_2, i);
        i++;
    }
 
    return 0;
}
----------------------------------------------------------------------------------
4
----------------------------------------------------------------------------------
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
----------------------------------------------------------------------------------
5
----------------------------------------------------------------------------------
#include <avr/io.h>
 
struct pole
{
        volatile char b0 : 1; //zmienna nie podlegajaca procesowi optymalizacji
        volatile char b1 : 1;
        volatile char b2 : 1;
        volatile char b3 : 1;
        volatile char b4 : 1;
        volatile char b5 : 1;
        volatile char b6 : 1;
        volatile char b7 : 1;
};
 
#define LED3 ((*((struct pole *) &PORTA)).b3)
#define LEDDDR3 ((*((struct pole *) &DDRA)).b3)
 
int main(void)
{      
        LEDDDR3 = 1;
 
        while(1)
        {
                LED3 ^= 1;
        }
        return 0;
}
