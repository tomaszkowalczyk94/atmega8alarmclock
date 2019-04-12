/*
 * initializer.h
 *
 * Created: 2019-04-12 23:23:07
 *  Author: abc
 */ 


#ifndef INITIALIZER_H_
#define INITIALIZER_H_

#define MODE_BUTTON PD5
#define SET_BUTTON PD6

#define SPEAKER_PIN_1 PB1
#define SPEAKER_PIN_2 PB2

void main_display_initialize();
void button_initialize();
void speaker_initialize();
void display_timer_initialize() ;
void time_timer_initialize();
void sound_timer_initialize() ;

#endif /* INITIALIZER_H_ */