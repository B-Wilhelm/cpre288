#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"
#include "uart.h"
#include "adc.h"
#include <math.h>

int main(void){
    //Enable ADC0 using SS0
    adc_init();        //initializes needed functions
    lcd_init();
    adc_handler_en();
    uart_init();


    while(1){
        int i = 0;
        int data = 0;
        int raw = 0;
        for(i=0; i<10; i++){
            int raw_data = adc_read(ADC0_SSMUX0_R); // reads sensor data from bot

            int calibrate = 43666/(pow((raw_data), 1.029)); // converts raw sensor data to known distances in cm
            raw = raw+raw_data;
            data = data+calibrate;
            timer_waitMillis(100);
        }

        raw = raw/10;  //raw average for graphing purposes
        data= data/10;  // average to get a non-changing disance
        char text [100] = {0};
        sprintf(text, "%d\t%d\r\n", data, raw); // prints to putty
        uart_sendStr(text);


        adc_polling();


        lcd_printf("%d", data); // prints to lcd on bot

    }

}
