/*
 * timer.h
 *
 *  Created on: Mar 15, 2019
 *      @author Isaac Rex
 */

#ifndef TIMER3B_H_
#define TIMER3B_H_

#include "Timer.h"

void send_pulse(void);

void portb_init(void);

void TIMER3B_init(void);
int ping_read();

#endif /* TIMER_H_ */
