#include "timer.h"
#include "lcd.h"
#include "driverlib/interrupt.h"
#include "servo.h"
#include "button.h"
#include "TIMER3B.h"
#include "uart.h"
#include "math.h"
#include "adc2.h"
#include "open_interface.h"
#include "move.h"

void step1(void){
	int flag = 0;
	while(flag = 0){
		obj_det();
		
		for(i=0;i<=181;i++){
			if(object_storage[i].size == 0){ //narrow object
				flag = 1;
				turn_towards();
			}
			if(object_storage[i].size == 1){ // wide object
				
			}
		

		move_forward(sensor_data,35);
	}
}

int turn_towards(void){ //points towards narrow object
	int end = 0;
	for(i=0;i<=181;i++){
		if(object_storage[i].size == 0){ //narrow object
			if(object_storage[i].angle < 90){
				turn_counterclockwise(oi_t *sensor_data,(90-object_storage[i].angle)); //points at object
				flag = 1;  //flag for narrow object detected
				break;
			}
			else{
				turn_clockwise(oi_t *sensor_data,(object_storage[i].angle-90)); //points at object
				break;
			}
		}
		if(object_storage[i].size == 1){ // wide object
		}
	}
}