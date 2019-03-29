/*
 * main.c
 *
 *  Created on: Mar 21, 2019
 *      Author: tomek
 */

#include <avr/io.h>
#include <util/delay.h>

#include "led_display.h"



int main() {


	pins_data.dig_1_ddr = &DDRB;
	pins_data.dig_2_ddr = &DDRB;
	pins_data.dig_3_ddr = &DDRB;
	pins_data.dig_4_ddr = &DDRB;
	pins_data.dig_special_ddr = &DDRB;

	pins_data.dig_1_port = &PORTB;
	pins_data.dig_2_port = &PORTB;
	pins_data.dig_3_port = &PORTB;
	pins_data.dig_4_port = &PORTB;
	pins_data.dig_special_port = &PORTB;

	pins_data.dig_1_port_index = PB1;
	pins_data.dig_2_port_index = PB2;
	pins_data.dig_3_port_index = PB3;
	pins_data.dig_4_port_index = PB4;
	pins_data.dig_special_port_index = PB5;

	pins_data.led_a_ddr = &DDRC;
	pins_data.led_b_ddr = &DDRC;
	pins_data.led_c_ddr = &DDRC;
	pins_data.led_d_ddr = &DDRC;
	pins_data.led_e_ddr = &DDRC;
	pins_data.led_f_ddr = &DDRC;
	pins_data.led_g_ddr = &DDRB;

	pins_data.led_a_port = &PORTC;
	pins_data.led_b_port = &PORTC;
	pins_data.led_c_port = &PORTC;
	pins_data.led_d_port = &PORTC;
	pins_data.led_e_port = &PORTC;
	pins_data.led_f_port = &PORTC;
	pins_data.led_g_port = &PORTB;

	pins_data.led_a_port_index = PC0;
	pins_data.led_b_port_index = PC1;
	pins_data.led_c_port_index = PC2;
	pins_data.led_d_port_index = PC3;
	pins_data.led_e_port_index = PC4;
	pins_data.led_f_port_index = PC5;
	pins_data.led_g_port_index = PB0;

	init_led_display();



	while(1)
	{
		_delay_ms(2000);
		display();
	}


//
//	DDRC = 0b11111111;
//	PORTC = 0;
//
//	DDRB = 0b00111110;
//
//	int i = 0;
//
//	while (1) //Pętla główna
//	{
//		PORTB = 0b00000010 << i;
//
//
//		_delay_ms(4000);
//
//		i++;
//		if(i>5) {
//			i=0;
//		}
//	}



}
