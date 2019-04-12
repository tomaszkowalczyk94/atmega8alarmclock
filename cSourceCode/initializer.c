#include "initializer.h"
#include "led_display.h"



void main_display_initialize()
{
	// ============= pin initializing =============
	int i;

	pins_data.dig_ddr[DIG_1] = &DDRD;
	pins_data.dig_port[DIG_1] = &PORTD;
	pins_data.dig_port_index[DIG_1] = PD3;
	
	pins_data.dig_ddr[DIG_2] = &DDRD;
	pins_data.dig_port[DIG_2] = &PORTD;
	pins_data.dig_port_index[DIG_2] = PD4;
	
	pins_data.dig_ddr[DIG_3] = &DDRB;
	pins_data.dig_port[DIG_3] = &PORTB;
	pins_data.dig_port_index[DIG_3] = PB3;
	
	pins_data.dig_ddr[DIG_4] = &DDRB;
	pins_data.dig_port[DIG_4] = &PORTB;
	pins_data.dig_port_index[DIG_4] = PB4;
	
	pins_data.dig_ddr[DIG_SPECIAL] = &DDRB;
	pins_data.dig_port[DIG_SPECIAL] = &PORTB;
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
}

void button_initialize()
{
	DDRD &= ~(1<<MODE_BUTTON);
	DDRD &= ~(1<<SET_BUTTON);

	PORTD |= (1<<MODE_BUTTON);
	PORTD |= (1<<SET_BUTTON);
}

void speaker_initialize()
{
	DDRB |= (1<<SPEAKER_PIN_1);
	DDRB |= (1<<SPEAKER_PIN_2);
	
	PORTB |= (1<<SPEAKER_PIN_1);
	PORTB &= ~(1<<SPEAKER_PIN_2);
}

void display_timer_initialize() 
{
	// timer 0
	TCCR0 |= (1<<CS01); // clk. 8 preskaler
	TIMSK |= (1<<TOIE0); //enable interputs
}

void time_timer_initialize()
{
	// ================ timer2 (for time) initialize by documetation (page 117) ================
	TIMSK &= ~(1<<TOIE2); // disable timer2 interrupts
	
	ASSR |= (1<<AS2); // set timer2 to asynchronous mode
	TCNT2 = 0;
	TCCR2 |= _BV(CS22) | _BV(CS20) ;// set prescaler to 1/128
	while (ASSR&((1<<TCN2UB)|(1<<TCR2UB)));//wait for registers update
	TIMSK |= (1<<TOIE2);  // enable timer2 interrupts
}

void sound_timer_initialize() 
{
	// ================= timer 1 sound initialize ======================
	TCCR1A |= (_BV(COM1A0)); //Toggle OC1A/OC1B on Compare Match
	
	TCCR1B |= (1 << WGM12); // select CTC mode

	TCCR1B |= (1 << CS11); // preskaler = 63
	TCCR1B |= (1 << CS10);
	
	OCR1A = 312; //default value
}



