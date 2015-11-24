/**
 * Praktikum Finale: The Pong-Pong project
 * Final project for embedded system design experiment course.
 *
 * Created by:
 * * Fadhli Dzil Ikram (13212035)
 * * Febby Purnama M. (13212041)
 *
 */

#ifndef MAIN_H_
#define MAIN_H_

/* Library includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* LPC-specific includes */
#include <cr_section_macros.h>
#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_ssp.h"
#include "joystick.h"
#include "oled.h"

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Local includes */
#include "fsm.h"
#include "output.h"
#include "game.h"

/* Constant definition */
#define TASK_FSM_DELAY 100 // in ms

/* Function prototypes */
int main (void);
void vFSMTask (void *);
static void init_ssp(void);

/* FreeRTOS related function prototypes */
void vApplicationMallocFailedHook(void);
void vApplicationStackOverflowHook(xTaskHandle *, signed char *);
void vApplicationIdleHook(void);
void vApplicationTickHook(void);

#endif /* MAIN_H_ */
