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
