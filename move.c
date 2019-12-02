#include "open_interface.h"
#include "Timer.h"
#include "lcd.h"
#include "move.h"

void bot_init(void){


    //Complete this code for configuring the  (GPIO) part of UART initialization

    SYSCTL_RCGCUART_R |= 0b00000010;
    timer_waitMillis(1);

    SYSCTL_RCGCGPIO_R |= 0b000010;
    timer_waitMillis(1);            // Small delay before accessing device after turning on clock
    GPIO_PORTB_AFSEL_R |= 0b00000011;

    GPIO_PORTB_PCTL_R &= 0xffffff11;     // Force 0's in the desired locations
    GPIO_PORTB_PCTL_R |= 0x11;     // Force 1's in the desired locations

    GPIO_PORTB_DEN_R |= 0x11;

    GPIO_PORTB_DIR_R &= 0xffffff10;      // Force 0's in the desired locations
    GPIO_PORTB_DIR_R |= 0x10;      // Force 1's in the desired locations
}
void move_Back(oi_t *sensor_data, int centi){

    double sum = 0;
    oi_setWheels(-125, -125); // move back; full speed

    while (sum < centi) {
        oi_update(sensor_data);
        sum -= sensor_data->distance;

    }


    oi_setWheels(0, 0); // stop
    timer_waitMillis(300);
}
void move_forward(oi_t *sensor_data, int centi){

    int sum = 0;
    // move forward; full speed

    while (1) {
        line_detect(sensor_data);
        cliff_detect(sensor_data);
        oi_setWheels(125, 125);

        oi_update(sensor_data);
        sum += sensor_data->distance;

        int x = sensor_data->bumpLeft;
        int y= sensor_data->bumpRight;


        if(y==1){

            oi_setWheels(0, 0);

            move_Back(sensor_data, 140);

            turn_counterclockwise(sensor_data, 70);

            move_forward(sensor_data, 175);

            turn_clockwise(sensor_data, 70);

            move_forward(sensor_data,140);

        }
        if(x==1){ //

            oi_setWheels(0, 0);

            move_Back(sensor_data, 140);

            turn_clockwise(sensor_data, 70);

            move_forward(sensor_data, 175);

            turn_counterclockwise(sensor_data, 70);


            move_forward(sensor_data,140);

        }




    }
    oi_setWheels(0, 0); // stop


}



void turn_clockwise(oi_t *sensor_data, int degrees){

    //int turn_distance;
    double sum2 = 0;


    oi_setWheels(-125,125);

    while (sum2 < degrees) {
        oi_update(sensor_data);
        sum2 -= sensor_data->angle;
    }
    oi_setWheels(0, 0); // stop
    timer_waitMillis(300);
}

void turn_counterclockwise(oi_t *sensor_data, int degrees){

    //int turn_distance;
    double sum2 = 0;


    oi_setWheels(125,-125);

    while (sum2 < degrees) {
        oi_update(sensor_data);
        sum2 += sensor_data->angle;
    }
    oi_setWheels(0, 0); // stop
    timer_waitMillis(300);
}

void cliff_detect(oi_t *sensor_data){
    oi_update(sensor_data);
    if(sensor_data->cliffLeft==1){
        move_Back(sensor_data,10);
        turn_clockwise(sensor_data,30);
    }
    if(sensor_data->cliffFrontLeft==1){
        move_Back(sensor_data,10);
        turn_clockwise(sensor_data,90);
    }
    if(sensor_data->cliffFrontRight==1){
        move_Back(sensor_data,10);
        turn_counterclockwise(sensor_data,90);
    }
    if(sensor_data->cliffRight==1){
        move_Back(sensor_data,10);
        turn_counterclockwise(sensor_data,30);
    }
}
void line_detect(oi_t *sensor_data){
    oi_update(sensor_data);
    if(sensor_data->cliffFrontLeftSignal>2600){
        move_Back(sensor_data,10);
        turn_clockwise(sensor_data,30);
    }
    if(sensor_data->cliffFrontLeftSignal>2600){
        move_Back(sensor_data,10);
        turn_clockwise(sensor_data,90);
    }
    if(sensor_data->cliffFrontRightSignal>2600){
        move_Back(sensor_data,10);
        turn_counterclockwise(sensor_data,90);
    }
    if(sensor_data->cliffRightSignal>2600){
        move_Back(sensor_data,10);
        turn_counterclockwise(sensor_data,30);
    }


}
