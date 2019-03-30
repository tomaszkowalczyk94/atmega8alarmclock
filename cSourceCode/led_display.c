#include "led_display.h"

#include <stdbool.h>

void init_led_display()
{
	//======= initialize pins
	int i, y;

	for(i=0; i<5 ; i++)
	{
		*pins_data.dig_ddr[i] |= (1<<pins_data.dig_port_index[i]);
	}

	for(i=0; i<9 ; i++)
	{
		*pins_data.led_ddr[i] |= (1<<pins_data.led_port_index[i]);
	}

	//======= initialize state of variable "display_state"
	for(i=0; i<5 ; i++)
	{
		for(y=0 ; y<9 ; y++) {
			display_state[i][y] = false;
		}
	}

}

void display()
{
	turn_off_all();

	static int display_segment_index = 0;

	turn_on_digit(display_segment_index);

	for(int i=0; i<9; i++)
	{
		if(display_state[display_segment_index][i]) {
			turn_on_led(i);
		}
	}

	display_segment_index ++;
	if(display_segment_index>4) {
		display_segment_index = 0;
	}
}

void set_display_state_by_4_digit(int digit1, int digit2, int digit3, int digit4, bool colon_state)
{
	set_digit(DIG_1, digit1);
	set_digit(DIG_2, digit2);
	set_digit(DIG_3, digit3);
	set_digit(DIG_4, digit4);

	display_state[DIG_SPECIAL][LED_COLON] = colon_state;
}

void set_display_state_by_2_digit(int digit1, int digit2, bool colon_state)
{
	digit1 %=100;
	digit2 %=100;

	int physical_digit_1 = digit1/10;
	int physical_digit_2 = digit1%10;
	int physical_digit_3 = digit2/10;
	int physical_digit_4 = digit2%10;

	set_display_state_by_4_digit(
			physical_digit_1,
			physical_digit_2,
			physical_digit_3,
			physical_digit_4,
			colon_state
	);
}

void set_digit(int digit_index, int digit)
{
	if(digit_index == DIG_SPECIAL) {
		return;
	}

	switch(digit) {
		case 0:
			display_state[digit_index][LED_A] = true;
			display_state[digit_index][LED_B] = true;
			display_state[digit_index][LED_C] = true;
			display_state[digit_index][LED_D] = true;
			display_state[digit_index][LED_E] = true;
			display_state[digit_index][LED_F] = true;
			display_state[digit_index][LED_G] = false;
			break;
		case 1:
			display_state[digit_index][LED_A] = false;
			display_state[digit_index][LED_B] = true;
			display_state[digit_index][LED_C] = true;
			display_state[digit_index][LED_D] = false;
			display_state[digit_index][LED_E] = false;
			display_state[digit_index][LED_F] = false;
			display_state[digit_index][LED_G] = false;
			break;
		case 2:
			display_state[digit_index][LED_A] = true;
			display_state[digit_index][LED_B] = true;
			display_state[digit_index][LED_C] = false;
			display_state[digit_index][LED_D] = true;
			display_state[digit_index][LED_E] = true;
			display_state[digit_index][LED_F] = false;
			display_state[digit_index][LED_G] = true;
			break;
		case 3:
			display_state[digit_index][LED_A] = true;
			display_state[digit_index][LED_B] = true;
			display_state[digit_index][LED_C] = true;
			display_state[digit_index][LED_D] = true;
			display_state[digit_index][LED_E] = false;
			display_state[digit_index][LED_F] = false;
			display_state[digit_index][LED_G] = true;
			break;
		case 4:
			display_state[digit_index][LED_A] = false;
			display_state[digit_index][LED_B] = true;
			display_state[digit_index][LED_C] = true;
			display_state[digit_index][LED_D] = false;
			display_state[digit_index][LED_E] = false;
			display_state[digit_index][LED_F] = true;
			display_state[digit_index][LED_G] = true;
			break;
		case 5:
			display_state[digit_index][LED_A] = true;
			display_state[digit_index][LED_B] = false;
			display_state[digit_index][LED_C] = true;
			display_state[digit_index][LED_D] = true;
			display_state[digit_index][LED_E] = false;
			display_state[digit_index][LED_F] = true;
			display_state[digit_index][LED_G] = true;
			break;
		case 6:
			display_state[digit_index][LED_A] = true;
			display_state[digit_index][LED_B] = false;
			display_state[digit_index][LED_C] = true;
			display_state[digit_index][LED_D] = true;
			display_state[digit_index][LED_E] = true;
			display_state[digit_index][LED_F] = true;
			display_state[digit_index][LED_G] = true;
			break;
		case 7:
			display_state[digit_index][LED_A] = true;
			display_state[digit_index][LED_B] = true;
			display_state[digit_index][LED_C] = true;
			display_state[digit_index][LED_D] = false;
			display_state[digit_index][LED_E] = false;
			display_state[digit_index][LED_F] = false;
			display_state[digit_index][LED_G] = false;
			break;
		case 8:
			display_state[digit_index][LED_A] = true;
			display_state[digit_index][LED_B] = true;
			display_state[digit_index][LED_C] = true;
			display_state[digit_index][LED_D] = true;
			display_state[digit_index][LED_E] = true;
			display_state[digit_index][LED_F] = true;
			display_state[digit_index][LED_G] = true;
			break;
		case 9:
			display_state[digit_index][LED_A] = true;
			display_state[digit_index][LED_B] = true;
			display_state[digit_index][LED_C] = true;
			display_state[digit_index][LED_D] = true;
			display_state[digit_index][LED_E] = false;
			display_state[digit_index][LED_F] = true;
			display_state[digit_index][LED_G] = true;
			break;
	}


}

void turn_off_all() {
	for(int i=0; i<5 ; i++) {
		*pins_data.dig_port[i] &= ~(1<<pins_data.dig_port_index[i]);
	}

	for(int i=0; i<9 ; i++) {
		*pins_data.led_port[i] |= (1<<pins_data.led_port_index[i]);
	}
}

void turn_on_digit(int digit_index)
{
	*pins_data.dig_port[digit_index] |= (1<<pins_data.dig_port_index[digit_index]);
}

void turn_on_led(int led_index)
{
	*pins_data.led_port[led_index] &= ~(1<<pins_data.led_port_index[led_index]);
}

