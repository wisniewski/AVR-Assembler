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