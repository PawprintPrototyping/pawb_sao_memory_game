#include "ch32fun.h"
#include <stdio.h>

// Project Includes
#include "periphs.h"
#include "game.h"
#include "attract.h"


void init(){
	init_gpio();
	seedrand();
}

void power_on_self_test(){
	for(uint8_t i = 0; i < 3; i++)
	{
		led_on(GREEN_LED);
		led_on(RED_LED);
		led_on(YELLOW_LED);
		led_on(BLUE_LED);
		Delay_Ms( 100 );
		led_off(GREEN_LED);
		led_off(RED_LED);
		led_off(YELLOW_LED);
		led_off(BLUE_LED);
		Delay_Ms( 100 );
	}
	beep(GREEN_SW, 10);
	beep(RED_SW, 10);
	beep(YELLOW_SW, 10);
	beep(BLUE_SW, 10);
}

int main()
{
	SystemInit();
    init();
	power_on_self_test();

	while(1){
		attract();
		Delay_Ms(1000);
		game_loop();
	}
}
