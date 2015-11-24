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
#include "main.h"

/** Global Variables **/
// Put FSM state on global variable to save the FSM task stack space
fsm_input_t i;
fsm_output_t o;
fsm_state_t s;
// Accelerometer offset var
int16_t xoff;

/** Main loop procedure **/
int main(void) {
	/* Local variables */
	int8_t x, y, z;
	/* Initialization code */
	init_ssp();
	init_i2c();
	joystick_init();
	oled_init();
	acc_init();
	oled_clearScreen(OLED_COLOR_WHITE);

	/* Accelerometer x offset initialization */
	acc_read(&x, &y, &z);
	xoff = 0 - x;

	/* FreeRTOS task initialization */
	xTaskCreate(vFSMTask, NULL, 240, NULL, 1, NULL);
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
	int8_t x, y, z;

	// Initialize last wake time tick count
	xLastWakeTime = xTaskGetTickCount();

	// Main loop
	while (1) {
		// Get joystick input
		i.joystick = joystick_read();
		// Get accelerometer input
		acc_read(&x, &y, &z);
		i.accel = x + xoff;
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

/* I2C initialization for Accelerometer */
static void init_i2c(void){
	PINSEL_CFG_Type PinCfg; // initialize a pin configuration structure
	/* Initialize I2C2 pin connect */
	PinCfg.Funcnum = 2; // set the pin to the #2 function -> I2C pin
	PinCfg.Portnum = 0; // pin in port number #0
	PinCfg.Pinnum = 10; // the #10 pin in that port number
	PINSEL_ConfigPin(&PinCfg); // config that pin
	PinCfg.Pinnum = 11; // the #11 pin in that port number
	PINSEL_ConfigPin(&PinCfg); // config that pin
	// Initialize I2C peripheral
	I2C_Init(LPC_I2C2, 100000); // set I2C function to have 100Khz clockrate
	/* Enable I2C1 operation */
	I2C_Cmd(LPC_I2C2, ENABLE); // enable/activate the I2C function
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
