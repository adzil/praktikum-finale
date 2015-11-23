#ifndef MAIN_H_
#define MAIN_H_

/* Library includes */
#include <stdio.h>
#include <stdlib.h>

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

/* Constant definition */
#define TASK_FSM_DELAY 100 // in ms

int main (void);
void vFSMTask (void *);
static void init_ssp(void);

#endif /* MAIN_H_ */
