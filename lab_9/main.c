#include <timer.h>
#include "lcd.h"
#include "driverlib/interrupt.h"
#include "servo.h"
#include "button.h"
#include <TIMER3B.h>
#include "uart.h"
//#include "adc.h"
#include <math.h>
#include "adc2.h"
#include "open_interface.h"
#include "move.h"


struct object{
    int distance;
    float width;
    int angle;

};
struct object object_storage[12];

int main(void){
    uart_init();  //initializations
    timer1_init();
    lcd_init();
    portb_init();
    adc_init();
    TIMER3B_init();
    bot_init();

    // runs the object detection function
    //obj_det();
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    while(1){

        oi_update(sensor_data);
        move_forward(sensor_data, 10);

    }


}



