#ifndef SOUND_H_
#define SOUND_H_

#include <avr/io.h>

#define SIZE_OF_SONG(x)  (sizeof(x) / sizeof((x)[0]))

void play_song(int *song_param, int size_of_song_param);
void refresh_tones(uint32_t ms_counter);
void stop_song();

void setTone(int hz);
void playTone(int tone, int duration);
void runtime_delay_ms(int ms);

#endif /* SOUND_H_ */