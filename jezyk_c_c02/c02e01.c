#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	//inicjalizacja
	DDRA = 0x01; //najmlodszy bit PA0 jako wyjscie
	PORTA = 0x03; //stan wysoki na PA0 + pin PA1 jako wejscie z podciągnięciem do Vcc
	//Vcc to przycisk nienaciśnięty, 0V - przycisk naciśnięty
	uint8_t status, old_status = 1, time_wait = 0, increase=0;
	
	while(1) //infinity loop
	{
		status = PINA & 0x02; //zmienna przechowujaca stan na pinie, gdzie
		PORTA = increase;
		if(!time_wait) //jesli czas == 0
		{
			if((status == 0) && (status != old_status)) //jesli naciskamy przycisk i jesli stan jest inny niz poprzednio
			{
				increase = (increase + 1) % 2;
				time_wait = 100; //znowu bedziemy musieli poczekac
			}
			old_status = status; //old = fresh ;)
		}
		else //poczekajmy 100 ms
		{
			time_wait--; //zmniejszamy co 1 ms
			_delay_ms(1);
		}
	}
	return 0;
}