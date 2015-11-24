/**
 * Praktikum Finale: The Pong-Pong project
 * Final project for embedded system design experiment course.
 *
 * Created by:
 * * Fadhli Dzil Ikram (13212035)
 * * Febby Purnama M. (13212041)
 *
 */

#ifndef FSM_H_
#define FSM_H_

/* Library includes */
#include <stdint.h>
#include <stdlib.h>

/* LPC specific includes */
#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_ssp.h"
#include "joystick.h"
#include "acc.h"

/* Local includes */
#include "game.h"

/* State constant definitions */
// Output state
#define output_main_splash 0
#define output_main_game 1
#define output_main_over 2
// Input state
#define input_joystick_mid 0x1
#define input_joystick_left 0x8
#define input_joystick_right 0x10
// Direction state
#define state_dir_left 1
#define state_dir_top 2

/* Struct definitions */
// Input state struct
typedef struct fsm_input_type {
	uint8_t joystick;
	int8_t accel;
} fsm_input_t;
// Output state struct
typedef struct fsm_output_type {
	uint8_t main;
	uint8_t xpos;
	uint8_t ypos;
	uint8_t xpad;
	uint16_t score;
} fsm_output_t;
// Direction state struct
typedef struct fsm_state_type {
	uint8_t dir;
} fsm_state_t;

/* Function prototypes */
void fsm (fsm_output_t *, fsm_input_t *);

#endif /* FSM_H_ */
