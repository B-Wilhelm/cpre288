#include <inc/tm4c123gh6pm.h>
#include <servo.h>
#include "driverlib/interrupt.h"
#include "lcd.h"
#include "timer.h"
#include <math.h>
#include "uart.h"

struct object{
    int distance;
    float width;
    int angle;
	int size; //0 is narrow or 1 is wide 
}
struct object object_storage[12];

void timer1_init(void){
    //***set GPIO PB5, turn on clk, alt. function, output, enable***
    SYSCTL_RCGCGPIO_R |= 0b00000010; //initialize port B clock
    timer_waitMillis(1);
    SYSCTL_RCGCTIMER_R  |= 0b10; //initialize Timer 1
    timer_waitMillis(1);

    GPIO_PORTB_DIR_R |= 0b100000;
    GPIO_PORTB_AFSEL_R |= 0b100000; //enables port b alt function
    GPIO_PORTB_DEN_R |= 0b100000; //enables port b digital function
    GPIO_PORTB_PCTL_R |= 0x700000;

    TIMER1_CTL_R &= 0b1111111011111111;   //disable timer to config
    TIMER1_CFG_R = 0x4;
    TIMER1_TBMR_R |= 0b1010;//set timer B to periodic mode and edge count mode and counts down
    TIMER1_TBMR_R &= ~(0b101); //the TnCMR bit to 0x0, and preserve the rest
    TIMER1_CTL_R &= 0b0011111111111111; //Sets tbwml to 0 to be not inverted
    TIMER1_CFG_R |= 0x4; //set size of timer to 16

    int pulse_period = 320000;
    int mid_width = 14550;

    TIMER1_TBILR_R |= pulse_period & 0xFFFF; //lower 16 bits of the interval
    TIMER1_TBPR_R |= pulse_period >> 16; //set the upper 8 bits of the interval

    TIMER1_TBPMR_R |= (pulse_period - mid_width) >> 16;
    TIMER1_TBMATCHR_R = (pulse_period - mid_width) & 0xFFFF; // if you want to move servo to the middle
    timer_waitMillis(20);
    TIMER1_CTL_R |= 0b000100000000; //enable timer

    timer_waitMillis(1);
}

void move_servo(unsigned degree){ // sets servo to degree indicated
    int pulse_period = 320000;

    //timer_waitMillis(25);
    int mid_width = round(-160*degree+27993);  // linear equation to convert from degrees to pulse width

    //    TIMER1_TBILR_R |= pulse_period & 0xFFFF; //lower 16 bits of the interval
    //    TIMER1_TBPR_R |= pulse_period >> 16; //set the upper 8 bits of the interval

    TIMER1_TBPMR_R |= (pulse_period - mid_width) >> 16;
    TIMER1_TBMATCHR_R = (pulse_period - mid_width) & 0xFFFF;

    timer_waitMillis(75); // maybe should be 100, trying to lower it
}

void obj_det(void){
    int ir_dist[181]={0};
    int ping_distance[181]={0};
    int angle[181]={0};
    int read_value;
    float dist_value;
    int object_l_edge_dist;
    int object_t_edge_dist;
    move_servo(0);
    timer_waitMillis(50);
    int i=0;
    int j=0;
    char data[1000];
    uart_sendStr("angle\t\tsonar\t\tIR\n\r");

    for(i = 0; i<=181;  i = i + 2){ //moves the servo from 0 to 180 degrees and takes 2 readings every 2 degrees.
        move_servo(i);
        ping_distance[i] = ping_read(); //stores a ping read distance in ith position of ping_distance
        read_value = adc_avg_distance();
        dist_value = pow(read_value,(-1.158));
        dist_value = dist_value * 99162;
        ir_dist[i] = dist_value;
        angle[i] = i;
        sprintf(data, "%d\t\t %d\t\t %d\n\r ", angle[i], ping_distance[i], ir_dist[i]);
        uart_sendStr(data);
    }

    int leading_edge;
    int trailing_edge;
    j = 0;
    float object_width;

    for(i=1;i<=181;i=i+2){ //iterates through every element of ir_dist in order to detect an object edge
        while(ir_dist[i-1] >= 50){ //checks for edges by evaluated distance at 2 angles ie. 2 and 4 so on
            if(i>181){ //breaks loop if waiting too long
                break;
            }
            i=i+2;
        }
        if(i>181){
			break; //exits for statement if previous wait loop exceeds 181
		} 
        while(abs(ir_dist[i-1]-ir_dist[i+1]) > 5){ // checks for leading edge of object
            i=i+2;
        }
        leading_edge = angle[i-1];
        object_l_edge_dist = (ping_distance[leading_edge]);
        while(abs(ir_dist[i-1]-ir_dist[i+1])<=5){ //checks for trailing edge of object
            i=i+2;
        }

        trailing_edge = angle[i-1];
        object_t_edge_dist = ping_distance[trailing_edge];
        int obj_location = (trailing_edge+leading_edge)/2;
        object_width = 2*(object_l_edge_dist*sin((3.1416/180)*((trailing_edge-leading_edge)/2)));
        if((object_width <15)&&(object_width >2)){ //stores object information if it falls within certain parameters. avoids detections of extremely large object (error)
            if(obj_location%2 ==1){
                obj_location++;
            }
            int object_dist = ping_distance[obj_location];
            object_storage[j].distance = object_dist;
            object_storage[j].angle = obj_location;
            object_storage[j].width = object_width;
            j++; //number of objects stored
        }
    }
    sprintf(data, "number of objects detected: "); //sends data to putty
    uart_sendStr(data);
    sprintf(data,"%d", j);
    uart_sendStr(data);
    sprintf(data, "\r\ndistance\t\tangle\t\twidth\r\n");
    uart_sendStr(data);

    for(i=0; i<j; i++){
        sprintf(data, "%d\t\t %d\t\t %f\n\r ", object_storage[i].distance, object_storage[i].angle, object_storage[i].width);
        uart_sendStr(data);
    }
	object_description; //small or large objects
    int smallest = 0;
    for(i=0;i<j;i++){//identifies smallest object
        if(object_storage[i].width<object_storage[smallest].width){
            smallest = i;
        }
    }

    sprintf(data,"%d", smallest);  // prints smalles object information to lcd and putty
    uart_sendStr(data);
    move_servo(object_storage[smallest].angle);
    sprintf(data, "\n\robject data\n\r");
    uart_sendStr(data);

    sprintf(data, "%d %d %f \n\r", object_storage[smallest].distance, object_storage[smallest].angle, object_storage[smallest].width);
    uart_sendStr(data);
    lcd_printf("distance  angle   width\n");
    lcd_printf("%d %d %f ", object_storage[smallest].distance, object_storage[smallest].angle, object_storage[smallest].width);
}

void object_description(void){
	for(i=0;i<j;i++){//identifies small objects
		if(object_storage[i].width<9) //small object 
			object_storage[i] = 0;
		}
		if(object_storage[i].width>9){ //large object
			object_storage[i] = 1;
		}
	}	
}

void full_scan(void){ //scans 360 degrees
	turn_clockwise(oi_t *sensor_data,90);
	obj_det();
	turn_counterclockwise(oi_t *sensor_data,180);
	obj_det();
}



