/**
 * Praktikum Finale: The Pong-Pong project
 * Final project for embedded system design experiment course.
 *
 * Created by:
 * * Fadhli Dzil Ikram (13212035)
 * * Febby Purnama M. (13212041)
 *
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

/* Library includes */
#include <stdint.h>

/* Local includes */
#include "fsm.h"
#include "oled.h"

/* Function prototypes */
void output (fsm_output_t *);
// intToString private variable */
#ifdef __OUTPUT_CFILE__
static void intToString(int, uint8_t *, uint32_t, uint32_t);
#endif

#endif /* OUTPUT_H_ */
