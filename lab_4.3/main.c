#include "button.h"
#include "timer.h"
#include "lcd.h"
#include "cyBot_uart.h"  // Functions for communicate between CyBot and Putty (via UART)                      // PuTTy: Buad=115200, 8 data bits, No Flow Control, No Party,  COM
#include "cyBot_Scan.h"  // For scan sensors

#define REPLACEME 0


int main(void) {

    int button_event_ptr;
    int button_num_ptr;
    lcd_init();
    button_init();
    //cyBot_uart_init();
        cyBot_uart_init_clean();     // Clean UART initialization, before running your UART GPIO init code
    //
        init_button_interrupts(&button_event_ptr, &button_num_ptr);

        //Complete this code for configuring the  (GPIO) part of UART initialization
        SYSCTL_RCGCUART_R |= 0b00000010;
        timer_waitMillis(1);

        SYSCTL_RCGCGPIO_R |= 0b000010;
        timer_waitMillis(1);            // Small delay before accessing device after turning on clock
        GPIO_PORTB_AFSEL_R |= 0b00000011;

        GPIO_PORTB_PCTL_R &= 0xffffff11;     // Force 0's in the desired locations
        GPIO_PORTB_PCTL_R |= 0x11;     // Force 1's in the desired locations

        GPIO_PORTB_DEN_R |= 0x11;

        GPIO_PORTB_DIR_R &= 0xffffff10;      // Force 0's in the desired locations
        GPIO_PORTB_DIR_R |= 0x10;      // Force 1's in the desired locations

        cyBot_uart_init_last_half();  // Complete the UART device initialization part of configuration

    /* while(1){
        char x= cyBot_getByte_blocking();  // writes from putty to cybot
        lcd_printf("%c", x);


        //writes from cybot to putty
        if(button_event_ptr == 1){
            cyBot_sendByte(button_num_ptr);
        }
    }
     */
    //part 3

    cyBOT_Scan_t *scan = {0,0};
    while(1){
        char x = cyBot_getByte_blocking();   //Send a byte over the UART from CyBot
        if(x =='m'){    //if m then scan every 5 degrees for 180 degrees
            cyBOT_init_Scan();
            char title[] = "Angle \t PING distance \t IR Raw value  \r\n";



            int i =0;
            while(title[i] != '\0'){
                cyBot_sendByte(title[i]);
                i++;
            }

            int y = 0;
            while(y <= 180){

                cyBOT_Scan(y, scan); //scan is a struct
                char msg[100];


                sprintf(msg, "%d \t %f \t %d \n\r", y, scan->sound_dist, scan->IR_raw_val);


                int i =0;
                while(msg[i] != '\0'){
                    cyBot_sendByte(msg[i]);
                    i++;
                }
                y = y + 5;
            }
        }
    }
}

