#include "periphs.h"

uint8_t led_to_sw(uint8_t led){
	switch(led){
		case GREEN_LED:
			return GREEN_SW;
		case RED_LED:
			return RED_SW;
		case YELLOW_LED:
			return YELLOW_SW;
		case BLUE_LED:
			return BLUE_SW;
	}
	return 0;
}


uint8_t sw_to_led(uint8_t sw){
	switch(sw){
		case GREEN_SW:
			return GREEN_LED;
		case RED_SW:
			return RED_LED;
		case YELLOW_SW:
			return YELLOW_LED;
		case BLUE_SW:
			return BLUE_LED;
	}
	return 0;
}


void beep(uint8_t sw, uint32_t time){
	uint32_t tone = 0;
	if(sw == GREEN_SW){
		tone = GREEN_NOTE;
	}
	else if(sw == RED_SW){
		tone = RED_NOTE;
	}
	else if(sw == YELLOW_SW){
		tone = YELLOW_NOTE;
	}
	else if(sw == BLUE_SW){
		tone = BLUE_NOTE;
	}
	else if (sw == 0){
		tone = LOSS_NOTE;
	}
	for(uint32_t i = 0; i < 10 * time; i++){
		funDigitalWrite( PIEZO_SPK, FUN_HIGH );
		Delay_Us(tone);
		funDigitalWrite( PIEZO_SPK, FUN_LOW );
		Delay_Us(tone);
	}
}

void init_gpio(){
    // Enable GPIOs
	funGpioInitAll();

    // Set up all the LEDs as outputs
	funPinMode( PC3, GPIO_Speed_10MHz | GPIO_CNF_OUT_PP );
	funPinMode( PC4, GPIO_Speed_10MHz | GPIO_CNF_OUT_PP );
	funPinMode( PC5, GPIO_Speed_10MHz | GPIO_CNF_OUT_PP );
	funPinMode( PC6, GPIO_Speed_10MHz | GPIO_CNF_OUT_PP );
    // Set up the buzzer as output
	funPinMode( PC0, GPIO_Speed_10MHz | GPIO_CNF_OUT_PP );
	// And do not power the buzzer
	funDigitalWrite( PIEZO_SPK, FUN_LOW );
	
    // Set up the buttons as inputs
	funPinMode( PD2, GPIO_CNF_IN_FLOATING );
	funPinMode( PD3, GPIO_CNF_IN_FLOATING );
	funPinMode( PD4, GPIO_CNF_IN_FLOATING );
	funPinMode( PD5, GPIO_CNF_IN_FLOATING );
}

void set_led(uint8_t led, uint8_t state){
	funDigitalWrite( led, !state); // Remember, the LEDs are hooked backwards, so invert the state
}

void led_on(uint8_t led){
	funDigitalWrite( led, FUN_LOW );
}

void led_off(uint8_t led){
	funDigitalWrite( led, FUN_HIGH );
}

void set_all_leds(uint8_t state){
    for(uint8_t i = 0; i < NUM_COLORS; i++){
        set_led(leds[i], state);
    }
}

uint8_t sw_read(uint8_t sw){
	// TODO: Some debouncing here would be nice. Could literally just be a delay at the end
	if(funDigitalRead(sw)){
        led_on(sw_to_led(sw));
		while(funDigitalRead(sw)){
			beep(sw, 2);	
		}
        led_off(sw_to_led(sw));
		Delay_Ms(5); // Debounce, this might be enough
		return 1;
	}
	return 0;
}

uint8_t poll_switches(){
	for(uint8_t sw_index = 0; sw_index < NUM_COLORS; sw_index++){
		if(sw_read(sws[sw_index])){
			return sws[sw_index];
		}
	}
	return 0;
}
