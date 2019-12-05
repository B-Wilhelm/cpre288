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
#include "parts.h"

struct object{
    int distance;
    float width;
    int angle;
    int size; //0 is narrow or 1 is wide
};
struct object object_storage[12];

void part1(void){
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    int closest_obj;
    int flag = flag_status();
    int i;
    int j;
    if(flag == 0){ //no object
        move_forward(sensor_data,45); //distance = object_storage[i].distance - 10;
    }
    if(flag == 1){ //narrow object
        narrow_only();
    }
    if(flag == 2){ // wide object
        turn_clockwise(sensor_data,45);
    }
    if(flag == 3){ // narrow and wide objects
        //logic needed
        multi_obj();

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
    int i = 0;
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


void narrow_only(void){ //points towards narrow object
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    int flag = 0;
    int i = 0;
    int temp = 0;

    for(i=0;i<=12;i++){
        if(object_storage[i].size == 0){ //narrow object
            if(object_storage[i].angle < 90){
                temp = 90-object_storage[i].angle;
                turn_counterclockwise(sensor_data,temp); //points at object
                flag = 1;  //flag for narrow object detected
                break;
            }
            else{
                temp = object_storage[i].angle-90;
                turn_clockwise(sensor_data,temp); //points at object
                break;
            }
        }
        //if(object_storage[i].size == 1){ // wide object
        //}
    }
}
void multi_obj(void){

    int closest_obj;
    int flag = flag_status();
    int i;
    int j;
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);


    for(i=0;i<(sizeof(object_storage)-1);i++){
        if( object_storage[i].size == 0){
            turn_counterclockwise(sensor_data,90-object_storage[i].angle);
            turn_counterclockwise(sensor_data, 90);
            obj_det();
            for(i=1; i<sizeof(object_storage)-1;i++){
                if(object_storage[i].distance<object_storage[i-1].distance){
                    closest_obj=i;
                }

            }
        }
    }
    if(object_storage[closest_obj].distance>25){}
    move_forward(sensor_data, 10);
    obj_det();

    for(j=1; j<sizeof(object_storage)-1;j++){
        if(object_storage[j].distance<object_storage[j-1].distance){
            closest_obj=j;


            if (object_storage[0].size == 0){
                if(object_storage[0].angle<90){
                    turn_counterclockwise(sensor_data,90-object_storage[0].angle);
                }
                if(object_storage[0].angle>90){
                    turn_clockwise(sensor_data,(object_storage[0].angle-90));
                }
                obj_det();

            }

        }
        if(((object_storage[closest_obj].distance>25)&&(object_storage[closest_obj].size==1))){}
        move_forward(sensor_data, 6);
        turn_clockwise(sensor_data, 90);
        obj_det();
    }

    if (object_storage[1].size == 0){
        turn_clockwise(sensor_data,object_storage[1].angle-90);
        turn_clockwise(sensor_data, 90);
        obj_det();
        for(j=1; j<sizeof(object_storage)-1;j++){
            if(object_storage[j].distance<object_storage[j-1].distance){
                closest_obj=i;
            }

        }

        if(((object_storage[closest_obj].distance>25)&&object_storage[closest_obj].size==1)){}
        move_forward(sensor_data, 6);
        turn_clockwise(sensor_data, 90);
        obj_det();
    }
}
