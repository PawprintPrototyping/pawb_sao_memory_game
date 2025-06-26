#include "attract.h"
#include "ch32fun.h"
#include "periphs.h"
#include "game.h"

#define ATTRACT_COUNTDOWN   20000

void attract(){
    uint16_t counter = ATTRACT_COUNTDOWN;
    while(1){
        seedrand();
        counter--;
        if(counter == 0){
            uint8_t led = leds[rand() % NUM_COLORS];
            led_on(led);
            Delay_Ms(10);
            led_off(led);
            counter = ATTRACT_COUNTDOWN;
        }
        if(poll_switches()){
            return;
        }
    }
}