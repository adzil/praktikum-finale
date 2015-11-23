/* Main includes */
#include "main.h"

/** Global Variables **/
// Put FSM state on global variable to save the FSM task stack space
fsm_input_t i;
fsm_output_t o;
fsm_state_t s;

/** Main loop procedure **/
int main(void) {
	/* Initialization code */
	init_ssp();
	joystick_init();
	oled_init();
	oled_clearScreen(OLED_COLOR_WHITE);

	/* FreeRTOS task initialization */
	xTaskCreate(vFSMTask, "FSM Task", 240, NULL, 1, NULL);
	// Finally, start the scheduler
	vTaskStartScheduler();

	// The code should not reach this point
	while(1);

    return 0;
}

/** FreeRTOS task procedures **/
/* Finite state machine (FSM) loop task */
void vFSMTask (void *pvParameters) {
	/* Variable declaration */
	portTickType xLastWakeTime;

	// Initialize last wake time tick count
	xLastWakeTime = xTaskGetTickCount();

	// Main loop
	while (1) {
		// Get joystick input
		i.joystick = joystick_read();
		// Process the input data on FSM
		fsm(&o, &i);
		// Output the data to OLED display
		output(&o);

		// Delay the task until the next tick time
		vTaskDelayUntil(&xLastWakeTime, TASK_FSM_DELAY / portTICK_RATE_MS);
	}

}

/** Initialization procedures **/
/* SSP initialization for OLED and Joystick */
static void init_ssp(void) {
	SSP_CFG_Type SSP_ConfigStruct;
	PINSEL_CFG_Type PinCfg;
	/*
	* Initialize SPI pin connect
	* P0.7 - SCK;
	* P0.8 - MISO
	* P0.9 - MOSI
	* P2.2 - SSEL - used as GPIO
	*/
	PinCfg.Funcnum = 2;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Portnum = 0;
	PinCfg.Pinnum = 7;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 8;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 9;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Funcnum = 0;
	PinCfg.Portnum = 2;
	PinCfg.Pinnum = 2;
	PINSEL_ConfigPin(&PinCfg);
	SSP_ConfigStructInit(&SSP_ConfigStruct);
	// Initialize SSP peripheral with parameter given in structure above
	SSP_Init(LPC_SSP1, &SSP_ConfigStruct);
	// Enable SSP peripheral
	SSP_Cmd(LPC_SSP1, ENABLE);
}

/** FreeRTOS' related functions **/
void vApplicationMallocFailedHook( void ) {
	/* This function will only be called if an API call to create a task, queue
	or semaphore fails because there is too little heap RAM remaining. */
	for( ;; );
}

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName ) {
	/* This function will only be called if a task overflows its stack.  Note
	that stack overflow checking does slow down the context switch
	implementation. */
	for( ;; );
}

void vApplicationIdleHook( void ) {
	/* This example does not use the idle hook to perform any processing. */
}

void vApplicationTickHook( void ) {
	/* This example does not use the tick hook to perform any processing. */
}
