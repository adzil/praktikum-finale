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
#include "output.h"

/* OLED output function */
// Should be called after the FSM module modify the output state.
void output (fsm_output_t * o) {
	// Last output storage
	static fsm_output_t lo;
	uint8_t buff[score_buffer + 2];

	// Checks if it's a new game
	if (o->main == output_main_game && lo.main != output_main_game) {
		// Clear the entire screen
		oled_clearScreen(OLED_COLOR_WHITE);
		// Give the last output a same value as the current one
		lo = *o;
	}

	// Checks if the main screen is in the splash mode
	if (o->main == output_main_splash && lo.main != output_main_splash) {
		// Clear the entire screen
		oled_clearScreen(OLED_COLOR_WHITE);
		// Splash screen goes here
		oled_putString(20,20,(uint8_t*)"Pong-Pong", OLED_COLOR_BLACK, OLED_COLOR_WHITE);
	} else if (o->main == output_main_game) {
		/* Redraw the game screen */
		// Draw the scoreboard
		intToString(o->score, buff, score_buffer, 10);
		oled_fillRect(score_xpos, score_ypos, score_buffer * char_width, score_ypos + char_height, OLED_COLOR_WHITE);
		oled_putString(score_xpos, score_ypos, buff, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
		// Erase last ball
		oled_fillRect(lo.xpos, lo.ypos, lo.xpos + ball_size, lo.ypos + ball_size, OLED_COLOR_WHITE);
		// Draw new ball
		oled_fillRect(o->xpos, o->ypos, o->xpos + ball_size, o->ypos + ball_size, OLED_COLOR_BLACK);
		// Erase last pad
		oled_rect(lo.xpad, pad_ypos, lo.xpad + pad_size, pad_ypos + pad_thick, OLED_COLOR_WHITE);
		// Draw new pad
		oled_rect(o->xpad, pad_ypos, o->xpad + pad_size, pad_ypos + pad_thick, OLED_COLOR_BLACK);
	} else if (o->main == output_main_over && lo.main != output_main_over) {
		// Game over screen goes here
		oled_putString(20,20,(uint8_t*)"Game Over", OLED_COLOR_BLACK, OLED_COLOR_WHITE);
	}

	// Update the last output with the current one
	lo = *o;
}

/* Integer to String conversion function */
static void intToString(int value, uint8_t *pBuf, uint32_t len, uint32_t base) {
	static const char* pAscii = "0123456789abcdefghijklmnopqrstuvwxyz";
	int pos = 0;
	int tmpValue = value;
	if (pBuf == NULL || len < 2) { return; }
	if (base < 2 || base > 36) { return; }
	if (value < 0) {
		tmpValue = -tmpValue;
		value = -value;
		pBuf[pos++] = '-';
	}

	do {
	pos++;
	tmpValue /= base;
	} while(tmpValue > 0);

	if (pos > len) { return; }
	pBuf[pos] = '\0';

	do {
		pBuf[--pos] = pAscii[value % base];
		value /= base;
	} while(value > 0);

	return;
}
