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

void part1(void){
	int flag = flag_status();
	if(flag = 0){ //no object
		move_forward(45); //distance = object_storage[i].distance - 10;
	}
	if(flag = 1){ //narrow object
		narrow_only();
	}
	if(flag = 2){ // wide object
		turn_clockwise(45);
	}
	if(flag = 3){ // narrow and wide objects
		//logic needed
	}
}

void part2(void){ //bot is pointed at narrow object and is within 10
	flag_status();
	
}

void part3(void){
	
}



int flag_status(void){
	int flag1 = 0; //narrow object
	int flag2 = 0; // wide object 
	//while(flag1 = 0 || flag2 = 0){
		obj_det();
		for(i=0;i<=181;i++){
			if(object_storage[i].size == 0){ //narrow object
				flag1 = 1;
			}
			if(object_storage[i].size == 1){ // wide object
				flag2 = 2;
			}
		}
	//}
	return (flag1 + flag2);
}


int narrow_only(void){ //points towards narrow object
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
		//if(object_storage[i].size == 1){ // wide object
		}
	}
}