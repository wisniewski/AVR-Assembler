/* obserwacja na porcie A, od PA0 do PA 4 */

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0x0f;
	uint8_t i=0;
	while(1)
	{
		PORTA = (1 << (++i % 4)); //kod 1 z 4
		_delay_ms(1000);
	}
	return 0;
}