/*
 * main.c
 *
 *  Created on: Mar 21, 2019
 *      Author: tomek
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "led_display.h"

uint32_t volatile seconds = 0;

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



	sei(); // enable global interrupts

	// ================ main loop =============
	while(1)
	{
		_delay_ms(2);
		//display();
	}
}

ISR(TIMER2_OVF_vect)
{
	seconds += 1;

	set_display_state_by_2_digit(seconds, seconds, true);
}

ISR(TIMER0_OVF_vect)
{
	display();
}
