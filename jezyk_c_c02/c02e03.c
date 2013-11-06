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