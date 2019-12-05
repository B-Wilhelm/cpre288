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

#include "TIMER3B.h"
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"
#include "lcd.h"

//How to program the interrupt handler to
//– Count the number of pulses
//– Calculate pulse width
//– Decode IR signals
//– And do many other functions …
//in main

volatile enum {LOW, HIGH, DONE} state;
volatile unsigned rising_time; // start time of the return pulse
volatile unsigned falling_time; // end time of the return pulse

volatile unsigned last_time = 0;
volatile unsigned current_time = 0;
volatile int update_flag = 0;
int numOverflow;

void portb_init(void){

    SYSCTL_RCGCGPIO_R |= 0b00000010; //initialize port B clock
    timer_waitMillis(1);
    //GPIO_PORTB_AFSEL_R &= 0b111110111; //disables port b alt function
    GPIO_PORTB_DEN_R |= 0b1000; //enables port b digital function
    GPIO_PORTB_PCTL_R |= 0x7000;
    //GPIO_PORTB_DIR_R |= 0b1000;  // sets port b to output(transmit)

}

//ping sensor related to ISR

void TIMER3B_Handler(void){


    //if state is low and an interrupt is called, it is now high, and you should store the time here
    if(state == LOW){
        state=HIGH;
        last_time = TIMER3_TBR_R;

    }


    //Conversely, store finished time if the opposite is true
    else if(state==HIGH){

        current_time = TIMER3_TBR_R;
        state = DONE;

    }

    //Clear the interrupt
    TIMER3_ICR_R |= 0x400;

}
void TIMER3B_init(void){


    SYSCTL_RCGCTIMER_R  |= 0b0000001000; //initialize Timer 3
    timer_waitMillis(1);


    TIMER3_CTL_R &= ~(0b100000000);     //disable, Edge Select.

    TIMER3_CFG_R|=  0x04;    //16-bit mode.

    //Double check this one!
    TIMER3_TBMR_R |= 0b111;     //Capture Mode, Edge-Time Mode, Count-down*.


    TIMER3_TBILR_R = 0xffff; //Set upper bound.
    TIMER3_TBPR_R = 0xff;  //Prescaler



    TIMER3_ICR_R |= 0x400; // clears ALL interrupt (ICR)
    TIMER3_IMR_R|= 0x400;     //Enable capture interrupt

    //set priority of 16/32-BIT TIMER 3B interrupt to 1.
    NVIC_PRI9_R |= 0x20;
    //enable interrupt for IRQ bit 36
    NVIC_EN1_R |= 0b10000;



    //reenable Timer3B, GPTMCTL
    TIMER3_CTL_R |= 0b110000000000;

    //GPIO_PORTB_PCTL_R |= 0x7000;

    IntRegister(INT_TIMER3B, TIMER3B_Handler);
    TIMER3_CTL_R |= 0b100000000; // ON
    IntMasterEnable();
}



// send out a pulse on PB3
void send_pulse(){

    TIMER3_IMR_R &= ~0x400;

    //Disable all the afsel stuff here
    GPIO_PORTB_AFSEL_R &= 0b111110111; //disables port b alt function
    GPIO_PORTB_DIR_R |= 0b1000; // set PB3 as output

    GPIO_PORTB_DATA_R &= 0b0000; // set PB3 to low
    GPIO_PORTB_DATA_R |= 0b1000; // set PB3 to high
    // wait at least 5 microseconds based on data sheet
    timer_waitMicros(5);
    GPIO_PORTB_DATA_R &= 0b0000; // set PB3 to low

    GPIO_PORTB_DIR_R &= 0b0111; // set PB3 as input
    //timer_waitMicros(500);
    //Reenable all the PCTL and AFSEL Stuff

    TIMER3_CTL_R |= 0b0000110000000000;
    GPIO_PORTB_AFSEL_R |= 0b0001000; //enables port b alt function
    GPIO_PORTB_PCTL_R |= 0x7000;



    //Quite possibly you'll have to clear interrupts here too
    TIMER3_ICR_R |= 0x400;
    //Also enable event capture interrupts here
    TIMER3_IMR_R|= 0x400;


}


// convert time in clock counts to single-trip distance in mm
unsigned time2dist(unsigned time){

    int distance = ((34000*time)/16000000)/2;

    return distance;

}

//
int ping_read(){

    int distance;
    send_pulse(); // send the starting pulse to PING

    //while grabbing information is not DONE, do nothing and wait
    while(state != DONE){

    }

    state = LOW;

    //when you're done waiting, state of the pulse is LOW
    //Then do calculations and return something
    distance = time2dist((last_time - current_time));

    if(last_time<current_time){
        unsigned long time_diff;

        time_diff =((unsigned long)1<<24) +last_time-current_time;

        distance = time2dist(time_diff);
        numOverflow++;



    }
    lcd_printf("dist: %d\noverflow: %d\nraw: %d\n", distance,numOverflow, (last_time-current_time));

return distance;

}

//int getNumOverflow(){
//    return numOverflow;
//}





