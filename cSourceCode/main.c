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

uint32_t volatile time = 0;
uint32_t volatile alarm = 0;

enum DEVICE_STATE {
	DISPLAY_CLOCK = 0,
	SET_ALARM_MIN = 1,
	SET_ALARM_H = 2,
	SET_CLOCK_MIN = 3,
	SET_CLOCK_H = 4
} device_state = DISPLAY_CLOCK;

#define MODE_BUTTON PD5
#define SET_BUTTON PD6

#define PIEZO_SPEAKER_PIN_1 PD0
#define PIEZO_SPEAKER_PIN_2 PD1

int koziolek[][2]={
                    523,125,
                    587,125,
                    659,250,
                    698,125,
                    659,125,
                    587,250,
                    523,250,
                    1047,250,
                    784,250,
                    523,250,
                    1047,250,
                    784,250,
                    523,250,
                    1047,250,
                    784,1000 };

bool button_is_pressed(int button)
{
	if(!(PIND & (1<<button))) {
		_delay_ms(25);

		while(!(PIND & (1<<button)));

		return true;
	}
	return false;
}

/*
Funkcja generuje sygnał prostokątny na wyprowadzeniach,
gdzie przyłączony jest  buzzer. Funkcja przyjmuje argumenty:
częstotliwość(Hz) sygnału i długość czasu trwania sygnału (ms).
*/
void beep(unsigned int frequency, unsigned int duration)
{
  unsigned int i,t,n;
  t = 125000/frequency;
  n = (250UL*duration)/t;

  PORTD |= PIEZO_SPEAKER_PIN_1;
  PORTD &= ~PIEZO_SPEAKER_PIN_2;
  for(i=0; i < n; i++)
  {
    PORTD ^= PIEZO_SPEAKER_PIN_1;
    PORTD ^= PIEZO_SPEAKER_PIN_2;
    _delay_loop_2(t);
  }
}

/*
Odgrywa melodyjkę dzwięk po dzwięku. Jako argumentów funkcja
oczekuje tablicy dzwięków oraz numerów pierwszego i ostatniego
dzwięku. Elementami tablicy dźwięków  są tablice o dwóch elementach
typu int (częstotliwość w Hz i długość trwania dzwięku w ms).
*/
void play(int nots[][2], unsigned int start, unsigned int stop)
{
   int n;

   for(n=start; n <= stop; n++)
        beep(nots[n][0], nots[n][1]);
}

int main() {

	// ============= pin initializing =============
	int i;
	for(i=0; i<5 ; i++)
	{
		pins_data.dig_ddr[i] = &DDRB;
		pins_data.dig_port[i] = &PORTB;
	}

	pins_data.dig_port_index[DIG_1] = PB1;
	pins_data.dig_port_index[DIG_2] = PB2;
	pins_data.dig_port_index[DIG_3] = PB3;
	pins_data.dig_port_index[DIG_4] = PB4;
	pins_data.dig_port_index[DIG_SPECIAL] = PB5;


	for(i=0; i<6 ; i++)
	{
		pins_data.led_ddr[i] = &DDRC;
		pins_data.led_port[i] = &PORTC;
	}

	pins_data.led_ddr[LED_G] = &DDRB;
	pins_data.led_port[LED_G] = &PORTB;

	pins_data.led_port_index[LED_A] = PC0;
	pins_data.led_port_index[LED_B] = PC1;
	pins_data.led_port_index[LED_C] = PC2;
	pins_data.led_port_index[LED_D] = PC3;
	pins_data.led_port_index[LED_E] = PC4;
	pins_data.led_port_index[LED_F] = PC5;
	pins_data.led_port_index[LED_G] = PB0;

	pins_data.led_ddr[LED_COLON] = &DDRD;
	pins_data.led_port[LED_COLON] = &PORTD;
	pins_data.led_port_index[LED_COLON] = PD7;

	init_led_display();

	// ================ timer0 initialize (for display)================

	TCCR0 |= (1<<CS01); // clk. 8 preskaler
	TIMSK |= (1<<TOIE0);

	// ================ timer2 initialize (for time)================

	TIMSK &= ~(1<<TOIE2); // disable timer2 interrupts

	ASSR |= (1<<AS2); // set timer2 to asynchronous mode

	TCCR2 = 0b0000101;// set prescaler to 1/128
	TIMSK |= (1<<TOIE2);  // enable timer2 interrupts

	// buttons setup
	DDRD &= ~(1<<MODE_BUTTON);
	DDRD &= ~(1<<SET_BUTTON);

	PORTD |= (1<<MODE_BUTTON);
	PORTD |= (1<<SET_BUTTON);

	//piezo speaker setup
	DDRD |= (1<<PIEZO_SPEAKER_PIN_1);
	DDRD |= (1<<PIEZO_SPEAKER_PIN_2);
	PORTD &= ~(1<<PIEZO_SPEAKER_PIN_1);
	PORTD &= ~(1<<PIEZO_SPEAKER_PIN_2);

	// =================
	TCCR1B |= (1 << WGM12); // Ustawienie trybu CT

	TCCR1B |= (1 << CS11); // Ustawienie preskalera na wartość 256
	TCCR1B |= (1 << CS10);

	OCR1A = 3; // Przepełnienie co 1 sekundę
	TIMSK |= (1<<OCIE1A);  // enable timer2 interrupts

	PORTD |= PIEZO_SPEAKER_PIN_1;
	PORTD &= ~PIEZO_SPEAKER_PIN_2;

	// ================ main loop =============
	sei();
	while(1)
	{

		if(button_is_pressed(MODE_BUTTON)){
			device_state++;
			if(device_state>SET_CLOCK_H) {
				device_state = DISPLAY_CLOCK;
				_delay_ms(300);
			}
		}

		switch(device_state) {
			case DISPLAY_CLOCK:
				setDisplayTimeInSec(time);
				break;
			case SET_ALARM_MIN:
				set_display_state_by_2_digit(1, 1, true);
				break;
			case SET_ALARM_H:
				set_display_state_by_2_digit(2, 2, true);
				break;
			case SET_CLOCK_MIN:
				set_display_state_by_2_digit(3, 3, true);
				break;
			case SET_CLOCK_H:
				set_display_state_by_2_digit(4, 4, true);
				break;

		}
	}
}


ISR(TIMER1_COMPA_vect)
{
	PORTD ^= PIEZO_SPEAKER_PIN_1;
	PORTD ^= PIEZO_SPEAKER_PIN_2;
}

ISR(TIMER2_OVF_vect)
{
	time += 1;
}

ISR(TIMER0_OVF_vect)
{
	display();
}
