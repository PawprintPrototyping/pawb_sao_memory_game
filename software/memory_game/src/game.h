#ifndef _GAME_H
#define _GAME_H

#include "ch32fun.h"

#define MAX_SCORE   10

static uint8_t seq[MAX_SCORE] = {0};
static uint8_t score = 0;

// Initialize the sequence
void init_seq();

// Seed the random number generator with its own randomness
// Do this constantly, so the sequence will be random when the user
// actually presses the button
void seedrand();

// Initialize the game
void init_game();

// Listen to the switches. If they are correct, return 1. Else, 0
uint8_t listen_switches();

// Play the sequence so far
void play_seq();

// Play the lose animation
void lose();

// Play the win animation
void win();

#endif