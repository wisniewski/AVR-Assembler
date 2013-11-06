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