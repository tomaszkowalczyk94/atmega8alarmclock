#include "sound.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

int *song;
int size_of_song;
bool is_playing = false;

int last_played_tone_index = -2;
uint32_t last_played_tone_ms_time = 0;

void play_song(int *song_param, int size_of_song_param)
{
	song = song_param;
	size_of_song = size_of_song_param;
	is_playing = true;
}

void refresh_tones(uint32_t ms_counter) 
{
	if(last_played_tone_index*2 == size_of_song -2) {
		stop_song();
	}
	
	if(is_playing == false) {
		return;
	}
	
	int next_tone_index = last_played_tone_index + 2;
	int next_tone_hz = song[next_tone_index];
	int next_tone_ms = song[next_tone_index+1];
	
	if(last_played_tone_ms_time+next_tone_ms < ms_counter) {
		TCCR1A |= (_BV(COM1A0));
		setTone(next_tone_hz);
		
		last_played_tone_ms_time = ms_counter;
		last_played_tone_index += 2;
	}
}

void stop_song() 
{
	is_playing = false;
	TCCR1A &= ~(1<<COM1A0); 
}

void setTone(int hz)
{
	OCR1A = (unsigned long)((unsigned long)4000000 / ((unsigned long)128*hz));
}

void playTone(int tone, int duration)
{
	setTone(tone);
	runtime_delay_ms(duration);
}

