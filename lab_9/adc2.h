/*
 * adc2.h
 *
 *  Created on: Oct 10, 2019
 *      Author: bwilhelm
 */

#ifndef ADC2_H_
#define ADC2_H_

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "timer.h"
#include "lcd.h"
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"

void adc_init(void);
int adc_get_raw(void);
//void adc_read(void);
int adc_avg_distance();

#endif /* ADC2_H_ */
