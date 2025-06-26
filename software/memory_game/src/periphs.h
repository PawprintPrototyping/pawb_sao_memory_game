#ifndef _PERIPHS_H
#define _PERIPHS_H

#include "ch32fun.h"

#define NUM_COLORS  4

#define GREEN_LED   PC3
#define RED_LED     PC4
#define YELLOW_LED  PC5
#define BLUE_LED    PC6

#define GREEN_SW    PD2
#define RED_SW      PD3
#define YELLOW_SW   PD4
#define BLUE_SW     PD5

#define PIEZO_SPK   PC0

#define GREEN_NOTE	1908	
#define RED_NOTE	1515
#define YELLOW_NOTE	1276
#define BLUE_NOTE	956
#define LOSS_NOTE	5745

static uint8_t leds[] = {GREEN_LED, RED_LED, YELLOW_LED, BLUE_LED};
static uint8_t sws[] = {GREEN_SW, RED_SW, YELLOW_SW, BLUE_SW};

// Given a LED, return its switch
uint8_t led_to_sw(uint8_t led);

// Given a switch, return its LED
uint8_t sw_to_led(uint8_t sw);

// Beep for a given time
void beep(uint8_t sw, uint32_t time);

// Init all the GPIOs
void init_gpio();

// Set the state of an LED
void set_led(uint8_t led, uint8_t state);

// Set the state of all the LEDs at once
void set_all_leds(uint8_t state);

// Turn on an LED
void led_on(uint8_t led);

// Turn off an LED
void led_off(uint8_t led);

// Read a switch and beep. Might need to debounce this
uint8_t sw_read(uint8_t sw);

// Poll all the switches, return the switch that is pressed, 0 otherwise
uint8_t poll_switches();


#endif