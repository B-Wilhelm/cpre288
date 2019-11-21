#include "open_interface.h"
#include "Timer.h"
#include "lcd.h"


void move_Back(oi_t *sensor_data, int centi){

    double sum = 0;
    oi_setWheels(-250, -250); // move forward; full speed

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

    while (sum < centi) {
        oi_setWheels(250, 250);

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

    int turn_distance;
    double sum2 = 0;


    oi_setWheels(-250,250);

    while (sum2 < degrees) {
        oi_update(sensor_data);
        sum2 -= sensor_data->angle;
    }
    oi_setWheels(0, 0); // stop
    timer_waitMillis(300);
}

void turn_counterclockwise(oi_t *sensor_data, int degrees){

    int turn_distance;
    double sum2 = 0;


    oi_setWheels(250,-250);

    while (sum2 < degrees) {
        oi_update(sensor_data);
        sum2 += sensor_data->angle;
    }
    oi_setWheels(0, 0); // stop
    timer_waitMillis(300);
}
