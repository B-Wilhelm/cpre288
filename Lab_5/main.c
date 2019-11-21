#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"
#include "uart.h"

int main(void){

    lcd_init();
    uart_init();
    uart_interupt_init();

    while(1){
//        int i = 0;
//        char text[20] = {0};
//        while(i<20 & text[i-1]!='\x0d'){  // checks length and character of text to determing when to stop collecting
//            text[i] = uart_receive();     // sets text{i] to character recieved from putty
//            uart_sendChar(text[i]);       // sends to putty
//            uart_sendChar('\r');          //resets curser in putty
//            lcd_printf("%c %d",text[i],i+1);
//            i++;
//        }
//        for(i = 0; i < strlen(text); i++){ // replaces the hex return character to \0
//            if(text[i] == '\x0d'){
//                text[i] = '\0';
//            }
//        }
//        lcd_printf("");     //prints the total message to the lcd of the bot
//        lcd_puts(text);
//        uart_sendChar('\n');
//        uart_sendStr(text);
//        uart_sendChar('\n');
//        uart_sendChar('\r');
    }
}




