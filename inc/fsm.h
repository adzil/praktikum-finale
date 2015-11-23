#ifndef FSM_H_
#define FSM_H_

#include <stdint.h>
#include "game.h"
#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_ssp.h"
#include "joystick.h"

#define output_main_splash 0
#define output_main_game 1
#define output_main_over 2

#define input_joystick_mid 1
#define input_joystick_left 2
#define input_joystick_right 4

#define state_dir_left 1
#define state_dir_top 2

typedef struct fsm_input_type {
	uint8_t joystick;
} fsm_input_t;

typedef struct fsm_output_type {
	uint8_t main;
	uint8_t xpos;
	uint8_t ypos;
	uint8_t xpad;
} fsm_output_t;

typedef struct fsm_state_type {
	uint8_t dir;
} fsm_state_t;

void fsm (fsm_output_t *, fsm_input_t *);

#endif /* FSM_H_ */
