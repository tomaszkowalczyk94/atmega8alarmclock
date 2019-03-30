/*
 * led_display.h
 *
 *  Created on: Mar 29, 2019
 *      Author: tomek
 */

#ifndef LED_DISPLAY_H_
#define LED_DISPLAY_H_

#include <avr/io.h>
#include <stdbool.h>

#define DIG_SPECIAL 0
#define DIG_1 1
#define DIG_2 2
#define DIG_3 3
#define DIG_4 4

#define LED_A 0
#define LED_B 1
#define LED_C 2
#define LED_D 3
#define LED_E 4
#define LED_F 5
#define LED_G 6
#define LED_DP 7
#define LED_UC 8
#define LED_LC 9

struct pins_data {

	volatile uint8_t *dig_ddr[5];
	volatile uint8_t *dig_port[5];
	uint8_t dig_port_index[5];

	volatile uint8_t *led_ddr[10];
	volatile uint8_t *led_port[10];
	uint8_t led_port_index[10];

} pins_data;


/**
 * array with state of display.
 * First index is digit index, like first digit in display, second digit, special digit etc.
 * 		allowed const: 	DIG_SPECIAL
 *						DIG_1
 *						DIG_2
 *						DIG_3
 *						DIG_4
 * Second index is led index.
 * 		allowed const:	LED_A
 *						LED_B
 *						LED_C
 *						LED_D
 *						LED_E
 *						LED_F
 *						LED_G
 *						LED_DP - dot point
 *						LED_UC - Only for digit
 *						LED_LC - Only for digit
 */
volatile bool display_state[5][10];

/**
 * initializing pin states, and turn off all leds
 */
void init_led_display();

/**
 * display leds specified by display_state array
 */
void display();

/**
 * set display state array by digit. all digit can be from 0 to 9 of course.
 */
void set_display_state(int digit1, int digit2, int digit3, int digit4, bool upperComaDot, bool lowerComaDot);

void set_digit(int digit_index, int digit);

void turn_off_all();

/**
 * turn on one digit segment.
 * 		allowed digit_index const: 	DIG_SPECIAL
 *									DIG_1
 *									DIG_2
 *									DIG_3
 *									DIG_4
 */
void turn_on_digit(int digit_index);

/**
 * turn on one led.
 */
void turn_on_led(int led_index);

#endif /* LED_DISPLAY_H_ */
