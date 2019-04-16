/*
 * main.c
 *
 *  Created on: Mar 21, 2019
 *      Author: tomek
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#include "led_display.h"
#include "sound.h"
#include "initializer.h"


// count of seconds
int volatile time = 0;
uint32_t volatile alarm = 0;



/*
 * is incremented by 3, with display refreshed. 
 * it isnt connect with "time" varible!!!.
 */
uint32_t volatile count_of_ms = 0;

enum DEVICE_STATE {
	DISPLAY_CLOCK = 0,
	SET_ALARM_MIN = 1,
	SET_ALARM_H = 2,
	SET_CLOCK_MIN = 3,
	SET_CLOCK_H = 4
} device_state = DISPLAY_CLOCK;



bool button_is_pressed(int button)
{
	if(!(PIND & (1<<button))) {
		_delay_ms(25);

		while(!(PIND & (1<<button)));

		return true;
	}
	return false;
}

static int barka_song[14] = {
	739,1500,
	739,250,
	659,250,
	739,250,
	783,250,
	739,250,
	659,250
};



int main() {

	main_display_initialize();
	button_initialize();
	speaker_initialize();
	display_timer_initialize();
	time_timer_initialize();
	sound_timer_initialize() ;
	sei();
	
	play_song(barka_song, 7);
	// ================ main loop =============
	while(1)
	{
		refresh_tones(count_of_ms);
		_delay_ms(40);
		/*
		if(button_is_pressed(MODE_BUTTON)){
			device_state++;
			if(device_state>SET_CLOCK_H) {
				device_state = DISPLAY_CLOCK;
				_delay_ms(300);
			}
		}
		*/
		switch(device_state) 
		{
			case DISPLAY_CLOCK: {
				setDisplayTimeInSec(time);
				break;
			}	
			case SET_ALARM_MIN: {
				set_display_state_by_2_digit(1, 1, true);
				break;
			}	
			case SET_ALARM_H: {
				set_display_state_by_2_digit(2, 2, true);
				break;
			}	
			case SET_CLOCK_MIN: {
				set_display_state_by_2_digit(3, 3, true);
				break;
			}	
			case SET_CLOCK_H: {
				set_display_state_by_2_digit(4, 4, true);
				break;
			}	
		}
		
	}
}

ISR(TIMER2_OVF_vect)
{
	time += 1;
}

ISR(TIMER0_OVF_vect)
{
	display();
	count_of_ms += 3;
}



