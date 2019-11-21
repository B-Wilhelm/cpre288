#include <timer.h>
#include<lcd.h>
#include <TIMER3B.h>
#include "driverlib/interrupt.h"
#include "uart_sonar.h"

int last_event_time;
int main(void){

    portb_init();
    TIMER3B_init();
    uart_init();
    lcd_init();


    while(1){

        ping_read();
        timer_waitMillis(100);

    }

    //configurations and inits
    //IntRegister(INT_TIMER3B, TIMER3B_Handler);

}



