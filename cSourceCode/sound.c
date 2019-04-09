#include "sound.h"

#include <avr/io.h>
#include <util/delay.h>


int barka_song[7][2] = {
	{739,1500},
	{739,250},
	{659,250},
	{739,250},
	{783,250},
	{739,250},
	{659,250}						  
};

void setTone(int hz)
{
	OCR1A = (unsigned long)((unsigned long)4000000 / ((unsigned long)128*hz));
}

void playTone(int tone, int duration)
{
	setTone(tone);
	runtime_delay_ms(duration);
}

void runtime_delay_ms(int ms)
{
	while (0 < ms)
	{
		_delay_ms(1);
		--ms;
	}
}
