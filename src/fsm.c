/* FSM.c - Finite State Machine for Pong-Pong Game.
 *
 */

#include "fsm.h"

void fsm (fsm_output_t * o, fsm_input_t * i) {
	/* Define static state variable */
	static fsm_state_t s;

	/* FSM state changer */
	if (o->main == output_main_splash || o->main == output_main_over) {
		if (i->joystick & input_joystick_mid) {
			o->main = output_main_game;
			o->xpos = (screen_x - ball_size) / 2;
			o->ypos = 10;
			o->xpad = (screen_x - pad_size) / 2;
			s.dir = 0;
		}
	} else {
		if (o->ypos <= 0) {
			s.dir &= ~state_dir_top;
		} else if (o->ypos >= screen_y - pad_thick - pad_offset - ball_size) {
			if (o->xpos > o->xpad - ball_size && o->xpos <= o->xpad + pad_size) {
				s.dir |= state_dir_top;
			} else {
				o->main = output_main_over;
			}
		}

		if (o->xpos <= 0) {
			s.dir &= ~state_dir_left;
		} else if (o->xpos >= screen_x - ball_size) {
			s.dir |= state_dir_left;
		}

		// Respond to joystick user input
		if (i->joystick & input_joystick_left) {
			if (o->xpad > 0) {
				o->xpad -= 1;
			}
		} else if (i->joystick & input_joystick_right) {
			if (o->xpad < screen_x - pad_size) {
				o->xpad += 1;
			}
		}
	}

	/* Output position changer */
	if (o->main == output_main_game) {
		if (s.dir & state_dir_top) {
			o->ypos -= 1;
		} else {
			o->ypos += 1;
		}

		if (s.dir & state_dir_left) {
			o->xpos -= 1;
		} else {
			o->xpos += 1;
		}
	}
}
