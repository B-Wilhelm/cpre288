#include <timer.h>
#include "lcd.h"
#include "driverlib/interrupt.h"
#include "servo.h"
#include "button.h"
#include <TIMER3B.h>
#include "uart.h"
#include <math.h>
#include "adc2.h"
#include "open_interface.h"
#include "move.h"
#include "parts.h" //need to make 


struct object{
    int distance;
    float width;
    int angle;
	int size; //0 is narrow 1 is wide
};
struct object object_storage[12];

int main(void){
	//initializations
    uart_init();
    timer1_init();
    lcd_init();
    portb_init();
    adc_init();
    TIMER3B_init();
    bot_init();

    
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    while(1){
        oi_update(sensor_data);
        move_forward(sensor_data, 10);
    }
	
	
	part1():
	part2();
	part3();
}



