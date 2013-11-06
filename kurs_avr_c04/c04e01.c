/* przerwania + Timer TC0 w trybie CTC */
 
#include <avr/io.h>
#include <avr/interrupt.h>
 
ISR(TIMER0_COMP_vect)
{
        DDRB = 0xff;
        PORTB++;
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