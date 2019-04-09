#ifndef SOUND_H_
#define SOUND_H_

#define PIEZO_SPEAKER_PIN_1 PB1
#define PIEZO_SPEAKER_PIN_2 PB2

#define SIZE_OF_SONG(x)  (sizeof(x) / sizeof((x)[0]))

extern int barka_song[7][2];

void setTone(int hz);
void playTone(int tone, int duration);
void runtime_delay_ms(int ms);

#endif /* SOUND_H_ */