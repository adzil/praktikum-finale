#ifndef FSM_H_
#define FSM_H_

typedef struct fsm_input_type {
	uint8_t joystick;
} fsm_input_t;

typedef struct fsm_output_type {
	uint8_t screen;
} fsm_output_t;

typedef struct fsm_state_type {
	uint8_t pos;
} fsm_state_t;

void fsm (fsm_output_t *, fsm_input_t *, fsm_state_t *);

#endif /* FSM_H_ */
