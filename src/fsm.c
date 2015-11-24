/**
 * Praktikum Finale: The Pong-Pong project
 * Final project for embedded system design experiment course.
 *
 * Created by:
 * * Fadhli Dzil Ikram (13212035)
 * * Febby Purnama M. (13212041)
 *
 */

/* Includes */
#include "fsm.h"

/* FSM function */
// The FSM function should be called on a periodic time after input sampling
void fsm (fsm_output_t * o, fsm_input_t * i) {
	/* Define static state variable */
	static fsm_state_t s;

	/* FSM state changer */
	if (o->main == output_main_splash || o->main == output_main_over) {
		if (i->joystick & input_joystick_mid) {
			o->main = output_main_game;
			o->xpos = rand() % screen_x;
			o->ypos = rand() % (screen_y / 2) + (screen_y / 4);
			o->xpad = rand() % screen_x;
			o->score = 0;
			s.dir = (rand() & state_dir_left) | state_dir_top;
		}
	} else {
		if (o->ypos <= ball_speed - 1) {
			s.dir &= ~state_dir_top;
		} else if (o->ypos >= screen_y - pad_thick - pad_offset - ball_size - ball_speed + 1) {
			if (o->xpos > o->xpad - ball_size && o->xpos <= o->xpad + pad_size) {
				s.dir |= state_dir_top;
				o->score += 1;
			} else {
				o->main = output_main_over;
			}
		}

		if (o->xpos <= ball_speed - 1) {
			s.dir &= ~state_dir_left;
		} else if (o->xpos >= screen_x - ball_size - ball_speed + 1) {
			s.dir |= state_dir_left;
		}

		// Respond to joystick user input
		if (i->joystick & input_joystick_left || (i->accel > accel_thresh_slow && i->accel < accel_thresh_fast)) {
			if (o->xpad > speed_slow - 1) {
				o->xpad -= speed_slow;
			}
		} else if (i->accel >= accel_thresh_fast) {
			if (o->xpad > speed_fast - 1) {
				o->xpad -= speed_fast;
			}
		} else if (i->joystick & input_joystick_right || (i->accel < -accel_thresh_slow  && i->accel > -accel_thresh_fast)) {
			if (o->xpad < screen_x - pad_size - speed_slow + 1) {
				o->xpad += speed_slow;
			}
		} else if (i->accel <= -accel_thresh_fast) {
			if (o->xpad < screen_x - pad_size - speed_fast + 1) {
				o->xpad += speed_fast;
			}
		}
	}

	/* Output position changer */
	if (o->main == output_main_game) {
		if (s.dir & state_dir_top) {
			o->ypos -= ball_speed;
		} else {
			o->ypos += ball_speed;
		}

		if (s.dir & state_dir_left) {
			o->xpos -= ball_speed;
		} else {
			o->xpos += ball_speed;
		}
	}
}
