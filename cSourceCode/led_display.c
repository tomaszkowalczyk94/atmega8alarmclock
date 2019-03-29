#include "led_display.h"

#include <stdbool.h>

void init_led_display()
{
	//initialize pins
	*pins_data.dig_1_ddr |= (1<<pins_data.dig_1_port_index);
	*pins_data.dig_2_ddr |= (1<<pins_data.dig_2_port_index);
	*pins_data.dig_3_ddr |= (1<<pins_data.dig_3_port_index);
	*pins_data.dig_4_ddr |= (1<<pins_data.dig_4_port_index);
	*pins_data.dig_special_ddr |= (1<<pins_data.dig_special_port_index);

	*pins_data.led_a_ddr |= (1<<pins_data.led_a_port_index);
	*pins_data.led_b_ddr |= (1<<pins_data.led_b_port_index);
	*pins_data.led_c_ddr |= (1<<pins_data.led_c_port_index);
	*pins_data.led_d_ddr |= (1<<pins_data.led_d_port_index);
	*pins_data.led_e_ddr |= (1<<pins_data.led_e_port_index);
	*pins_data.led_f_ddr |= (1<<pins_data.led_f_port_index);
	*pins_data.led_g_ddr |= (1<<pins_data.led_g_port_index);

	*pins_data.led_dp_ddr |= (1<<pins_data.led_dp_port_index);
	*pins_data.led_uc_ddr |= (1<<pins_data.led_uc_port_index);
	*pins_data.led_lc_ddr |= (1<<pins_data.led_lc_port_index);

	//initialize state
	struct digit_state start_digit_state;
	start_digit_state.a = false;
	start_digit_state.b = false;
	start_digit_state.c = false;
	start_digit_state.d = false;
	start_digit_state.e = false;
	start_digit_state.f = false;
	start_digit_state.g = false;
	start_digit_state.dp = false;

	display_state.digit_1_state = start_digit_state;
	display_state.digit_2_state = start_digit_state;
	display_state.digit_3_state = start_digit_state;
	display_state.digit_4_state = start_digit_state;
	display_state.uc = false;
	display_state.lc = false;

}

void display()
{
	turn_off_all();

	static int display_segment_index = 0;

	switch(display_segment_index) {
		/** comma */
		case 0:

			break;

		/** digit 1*/
		case 1:
			*pins_data.dig_1_port |= (1<<pins_data.dig_1_port_index);
			break;
		/** digit 2 */

		case 2:
			*pins_data.dig_2_port |= (1<<pins_data.dig_2_port_index);
			break;

		/** digit 3 */
		case 3:
			*pins_data.dig_3_port |= (1<<pins_data.dig_3_port_index);
			break;

		/** digit 4 */
		case 4:
			*pins_data.dig_4_port |= (1<<pins_data.dig_4_port_index);
			break;
	}

	display_segment_index ++;
	if(display_segment_index>5) {
		display_segment_index = 0;
	}
}



void turn_off_all() {
	*pins_data.dig_1_port &= ~(1<<pins_data.dig_1_port_index);
	*pins_data.dig_2_port &= ~(1<<pins_data.dig_2_port_index);
	*pins_data.dig_3_port &= ~(1<<pins_data.dig_3_port_index);
	*pins_data.dig_4_port &= ~(1<<pins_data.dig_4_port_index);
	*pins_data.dig_special_port &= ~(1<<pins_data.dig_special_port_index);

}

