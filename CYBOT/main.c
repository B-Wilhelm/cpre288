/// Simple 'Hello, world' program
/**
 * This program prints "Hello, world" to the LCD screen
 * @author Chad Nelson
 * @date 06/26/2012
 *
 * updated: phjones 9/3/2019
 * Describtion: Added timer_init call, and including Timer.h
 */

#include "Timer.h"
#include "lcd.h"
#include "button.h"
#include "open_interface.h"
#include "cyBot_uart.h"
#include "move.h"

void remote_control(void);


void main() {
    timer_init();
    lcd_init();
    cyBot_uart_init();
    button_init();
    while(1){

       remote_control();

        //uint8_t y = button_getButton();

        //if(button_getButton()){
        //cyBot_sendByte();}

    }
}

void remote_control(void){



    char x = cyBot_getByte();

    //cyBot_sendByte(x);

    if(x =='w'){
        oi_t *sensor_data = oi_alloc();
        oi_init(sensor_data);

        move_forward(sensor_data, 1);
        lcd_printf("w");
    }

    if(x== 's'){
        oi_t *sensor_data = oi_alloc();
        oi_init(sensor_data);

        move_Back(sensor_data, 1);
        lcd_printf("s");


    }



    if(x== 'a'){
        oi_t *sensor_data = oi_alloc();
        oi_init(sensor_data);

        turn_counterclockwise(sensor_data, 1);
        lcd_printf("a");

    }
    if(x== 'd'){
        oi_t *sensor_data = oi_alloc();
        oi_init(sensor_data);

        turn_clockwise(sensor_data, 1);
        lcd_printf("d");

    }
    else{

        lcd_printf("%c", x);
    }
}

