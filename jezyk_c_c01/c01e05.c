#include <avr/io.h>

int main(void)
{
	DDRA = 0xff; //255
	DDRA &= 0xab; //zeruje bity 2, 4 i 6 //zerowanie dzieki AND
	DDRA |= 0b01010100; //znowu ddra = 0xff / ustawianie dzieki OR
	DDRA ^= 0x01; //neguje najmlodszy bitu dzieki XOR

	return 0;
}