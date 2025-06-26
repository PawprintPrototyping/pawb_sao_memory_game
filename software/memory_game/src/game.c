#include "game.h"
#include "periphs.h"
#include "lib_rand.h"
#include "ch32fun.h"

#define ST_GAME_INIT    0
#define ST_INC_SCORE    1
#define ST_DO_PATTERN   2
#define ST_SW_LISTEN    3
#define ST_LOSE         4
#define ST_WIN          5

void init_seq(){
	for(uint8_t i = 0; i < MAX_SCORE; i++){
		seq[i] = leds[(rand() % 4)];
	}
}

void seedrand(){
	seed(rand());
}

void play_seq(){
    for(uint8_t i = 0; i < score; i++){
        led_on(seq[i]);
        beep(led_to_sw(seq[i]), 20);
        led_off(seq[i]);
        Delay_Ms(300);
    }
}

uint8_t listen_switches(){
    uint32_t timeout = 500000;
    for(uint8_t i = 0; i < score; i++){
        while(1){
            timeout--;
            uint8_t pressed = poll_switches();
            if(pressed){
                if(seq[i] != sw_to_led(pressed)){
                    return 0;
                }
                else{
                    break;
                }
            }
            if(timeout == 0){
                return 0;
            }
        }
    }
    return 1;
}

void lose(){
    set_all_leds(1);
    for(uint8_t i = 0; i < 4; i++){
        beep(0, 5);
        Delay_Ms(100);
    }
    set_all_leds(0);
}


void win(){
    for(uint8_t i = 0; i < NUM_COLORS; i++){
        beep(GREEN_SW, 5);
        Delay_Ms(100);
        set_all_leds(1);
        beep(RED_SW, 5);
        Delay_Ms(100);
        set_all_leds(0);
        beep(YELLOW_SW, 5);
        Delay_Ms(100);
        set_all_leds(1);
        beep(BLUE_SW, 5);
        Delay_Ms(100);
        set_all_leds(0);
        beep(YELLOW_SW, 5);
        Delay_Ms(100);
        set_all_leds(1);
        beep(RED_SW, 5);
        Delay_Ms(100);
        set_all_leds(0);
    }
    set_all_leds(0);
}

void init_game(){
    score = 0;
	init_seq();
}

void game_loop(){
    uint8_t game_state = ST_GAME_INIT;
    while(1){
        if(game_state == ST_GAME_INIT){
            init_game();
            game_state = ST_INC_SCORE;
        }
        if(game_state == ST_INC_SCORE){
            score++;
            if(score >= MAX_SCORE){
                game_state = ST_WIN;
            }
            else{
                game_state = ST_DO_PATTERN;
            }
        }
        if(game_state == ST_DO_PATTERN){
            play_seq();
            game_state = ST_SW_LISTEN;
        }
        if(game_state == ST_SW_LISTEN){
            if(listen_switches()){
                game_state = ST_INC_SCORE;
                Delay_Ms(1000);
            }
            else{
                game_state = ST_LOSE;
            }
        }
        if(game_state == ST_WIN){
            win();
            set_all_leds(0);
            return;
        }
        if(game_state == ST_LOSE){
            lose();
            set_all_leds(0);
            return;
        }
    }
}