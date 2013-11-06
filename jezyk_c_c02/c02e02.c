/* Ten program zostal napisany dla 4 przyciskow, ktore sa z 1 strony podlaczone do pinow PA1-PA4, a zdrugiej strony do masy
Oczywiscie na PA1 - PA4 jest pull-up. */

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	//inicjalizacja
	DDRA = 0x01; //najmlodszy bit PA0 jako wyjscie
	PORTA = 0x1f; //stan wysoki na PA0 + piny PA4-PA1 jako wejscie z podciągnięciem do Vcc
	//Vcc to przycisk nienaciśnięty, 0V - przycisk naciśnięty
	uint8_t status[4], old_status[4] = {1}, time_wait = 0;
	//teraz tablice beda przechowywac poszczegolne stany
	while(1) //infinity loop
	{
		for(int i = 0; i < 4; i++)
			status[i] = (PINA & (0x02 << i)); //zmienna przechowujaca stan na pinie
			
		if(!time_wait) //jesli czas == 0
		{
			for(int i = 0; i < 4; i++)
			{
				if((status[i] == 0) && (status[i] != old_status[i])) //jesli naciskamy przycisk i jesli stan jest inny niz poprzednio
				{
					PORTA ^= 0x01;
					time_wait = 3; //znowu bedziemy musieli poczekac
				}
			}
			for(int i = 0; i < 4; i++)
				old_status[i] = status[i]; //old = fresh ;)
		}
		else //poczekajmy 100 ms
		{
			time_wait--; //zmniejszamy co 1 ms
			_delay_ms(1);
		}
	}
	return 0;
}