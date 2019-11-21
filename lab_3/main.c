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

void main() {
    timer_init();
    lcd_init();

    int x = 1;

    button_init();


    while(x){

       int y= button_getButton();

    lcd_printf("%d", y);
    }



}
