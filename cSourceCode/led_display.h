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

struct pins_data {
	volatile uint8_t *dig_1_ddr;
	volatile uint8_t *dig_2_ddr;
	volatile uint8_t *dig_3_ddr;
	volatile uint8_t *dig_4_ddr;
	volatile uint8_t *dig_special_ddr;

	volatile uint8_t *dig_1_port;
	volatile uint8_t *dig_2_port;
	volatile uint8_t *dig_3_port;
	volatile uint8_t *dig_4_port;
	volatile uint8_t *dig_special_port;

	uint8_t dig_1_port_index;
	uint8_t dig_2_port_index;
	uint8_t dig_3_port_index;
	uint8_t dig_4_port_index;
	uint8_t dig_special_port_index;

	volatile uint8_t *led_a_ddr;
	volatile uint8_t *led_b_ddr;
	volatile uint8_t *led_c_ddr;
	volatile uint8_t *led_d_ddr;
	volatile uint8_t *led_e_ddr;
	volatile uint8_t *led_f_ddr;
	volatile uint8_t *led_g_ddr;
	volatile uint8_t *led_dp_ddr;
	volatile uint8_t *led_uc_ddr;
	volatile uint8_t *led_lc_ddr;

	volatile uint8_t *led_a_port;
	volatile uint8_t *led_b_port;
	volatile uint8_t *led_c_port;
	volatile uint8_t *led_d_port;
	volatile uint8_t *led_e_port;
	volatile uint8_t *led_f_port;
	volatile uint8_t *led_g_port;
	volatile uint8_t *led_dp_port;
	volatile uint8_t *led_uc_port;
	volatile uint8_t *led_lc_port;

	uint8_t led_a_port_index;
	uint8_t led_b_port_index;
	uint8_t led_c_port_index;
	uint8_t led_d_port_index;
	uint8_t led_e_port_index;
	uint8_t led_f_port_index;
	uint8_t led_g_port_index;
	uint8_t led_dp_port_index;
	uint8_t led_uc_port_index;
	uint8_t led_lc_port_index;

} pins_data;



struct digit_state {
	bool a;
	bool b;
	bool c;
	bool d;
	bool e;
	bool f;
	bool g;

	/**
	 * dot point
	 */
	bool dp;
};

struct display_state {
	struct digit_state digit_1_state;
	struct digit_state digit_2_state;
	struct digit_state digit_3_state;
	struct digit_state digit_4_state;

	bool uc;
	bool lc;

} display_state;


void init_led_display();

void display();

#endif /* LED_DISPLAY_H_ */
