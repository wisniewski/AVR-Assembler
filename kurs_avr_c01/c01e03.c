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