----------------------------------------------------------------------------------
2.2 / 1
----------------------------------------------------------------------------------

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

----------------------------------------------------------------------------------
2.2 / 2
----------------------------------------------------------------------------------

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

----------------------------------------------------------------------------------
2.2 / 3
----------------------------------------------------------------------------------

#include <avr/io.h>
#include <util/delay.h>

#define WAIT 100

int main(void)
{
	//inicjalizacja
	DDRA = 0xff; //jako wyjscie - 8 LEDow do manipulacji bitami
	PORTA = 0x01; //pa0 jako 1
	PORTB = 0x0f; //4 najmlodsze bity jako wejscia z pull-upem
	uint8_t status[4], old_status[4] = {1}, time_wait = 0, move = 0, choose_operation = 0, memory = 0;
	//teraz tablice beda przechowywac poszczegolne stany
	
	while(1) //infinity loop
	{
		for(int i = 0; i < 4; i++)
			status[i] = (PINB & (1 << i)); //zmienna przechowujaca stan na pinie
			
		if(!time_wait) //jesli czas == 0
		{
			if((status[0] == 0) && (status[0] != old_status[0])) //przesuwanie w lewo
			{
				move = (move + 1) % 8;
				PORTA = 1 << move; //wybieram poprzedni
				time_wait = WAIT; //znowu bedziemy musieli poczekac
			}
			else if((status[1] == 0) && (status[1] != old_status[1])) //przesuwanie w prawo
			{
				move = ((unsigned)(move - 1)) % 8;
				PORTA = 1 << move; //wybieram nastepny
				time_wait = WAIT; //znowu bedziemy musieli poczekac
			}
			else if((status[2] == 0) && (status[2] != old_status[2])) //akceptacja
			{
				switch(choose_operation)
				{
					case 0:
					{
						PORTA = (memory ^= (1 << move)); //negacja
					}
					break;
					case 1:
					{
						memory |= (1 << move);
						PORTA = memory; //ustawianie 1
					}
					break;
					case 2:
					{
						PORTA = (memory &= ~(1 << move)); //zerowanie
					}
					break;
				}
				time_wait = WAIT; //znowu bedziemy musieli poczekac
			}
			else if((status[3] == 0) && (status[3] != old_status[3])) //wybor operacji bitowej
			{
				choose_operation = (choose_operation + 1) % 3;
				time_wait = WAIT; //znowu bedziemy musieli poczekac
			}
			
			//zapamietywanie wartosci
			for(int i = 0; i < 4; i++)
				old_status[i] = status[i]; //old = fresh ;)
		}
		else //poczekajmy 100 ms
		{
			time_wait--; //zmniejszamy co 1 ms
			//_delay_ms(1);
		}
	}
	return 0;
}
