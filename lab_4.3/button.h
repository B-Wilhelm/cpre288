/*
 * button.h
 *
 *  Created on: Jul 18, 2016
 *      Author: Eric Middleton
 *
 * @edit: Phillip Jones 05/30/2019 : Removed uneeded helper functions
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include <stdbool.h>
#include "driverlib/interrupt.h"

volatile int *button_event_ptr;
volatile int *button_num_ptr;

//initialize the push buttons
void button_init();


///Non-blocking call
///Returns highest value button being pressed, 0 if no button pressed
uint8_t button_getButton();



// Initialize GPIO interrupts for buttons
void init_button_interrupts(int *,int *);

// handler for gpio event when button is pressed
void gpioe_handler();


#endif /* BUTTON_H_ */