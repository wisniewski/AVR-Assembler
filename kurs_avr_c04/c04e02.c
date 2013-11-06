/* przerwania + Timer TC0 w trybie CTC + pseudoopoznienie */
 
#include <avr/io.h>
#include <avr/interrupt.h>
 
ISR(TIMER0_COMP_vect) //10 k Hz = 100 us
{
        static uint32_t a = 10000;
        DDRB = 0xff;
       
        if(a == 0)
        {
                PORTB++;
                a = 10000;
        }
        else
                a--;
}
 
int main(void)
{
       
        TCCR0 |= _BV(CS01) | (1 << WGM01);
        TIMSK |= (1 << OCIE0);
        OCR0 = 99;
        sei(); 
        while(1);
        return 0;
}