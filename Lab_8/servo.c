/*
 *
 *   uart.c
 *
 *
 *
 *
 *
 *   @author
 *   @date
 */

#include <inc/tm4c123gh6pm.h>
#include <servo.h>
#include "driverlib/interrupt.h"
#include "lcd.h"
#include "timer.h"
#include "math.h"



void timer1_init(void)
{
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
    //TIMER1_TBPR_R |= 0xF;

    TIMER1_CFG_R |= 0x4; //set size of timer to 16


    int pulse_period = 320000;
    int mid_width = 14550;
    TIMER1_TBILR_R |= pulse_period & 0xFFFF; //lower 16 bits of the interval
    TIMER1_TBPR_R |= pulse_period >> 16; //set the upper 8 bits of the interval
    TIMER1_TBPMR_R |= (pulse_period - mid_width) >> 16;
    TIMER1_TBMATCHR_R = (pulse_period - mid_width) & 0xFFFF; // if you want to move servo to the middle
    timer_waitMillis(2000);
    TIMER1_CTL_R |= 0b000100000000; //enable timer

    timer_waitMillis(1);



}

void move_servo(unsigned degree){ // sets servo to degree indicated
    int pulse_period = 320000;

    timer_waitMillis(25);
    int mid_width =round(-160*degree+27993);  // linear equation to convert from degrees to pulse width

    TIMER1_TBILR_R |= pulse_period & 0xFFFF; //lower 16 bits of the interval
    TIMER1_TBPR_R |= pulse_period >> 16; //set the upper 8 bits of the interval

    TIMER1_TBPMR_R |= (pulse_period - mid_width) >> 16;
    TIMER1_TBMATCHR_R = (pulse_period - mid_width) & 0xFFFF;



    timer_waitMillis(20);

}

