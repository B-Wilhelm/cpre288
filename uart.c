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

#include "uart.h"
#include <Timer.h>
#include <inc/tm4c123gh6pm.h>

void uart_init(void){
    SYSCTL_RCGCUART_R |= 0b00000010; // initialize uart 1 clock
    timer_waitMillis(1);

    SYSCTL_RCGCGPIO_R |= 0b00000010; //initialize port B clock
    timer_waitMillis(1);

    GPIO_PORTB_AFSEL_R |= 0b00000011; // initialize Port B alternate functions onto pins 0 and 1

    GPIO_PORTB_PCTL_R &= 0xffffff11;     // port B port control set byte 1 to 0b00010001 to initialize recieve and transmit for port B uart1
    GPIO_PORTB_PCTL_R |= 0x11;

    GPIO_PORTB_DEN_R |= 0b11;   //port b digital enable force set

    GPIO_PORTB_DIR_R &= 0b11111110;      // set bit 0 to receive and bit 1 to transmit
    GPIO_PORTB_DIR_R |= 0b10;

    uint16_t iBRD = 8;
    uint16_t fBRD = 44;

    UART1_CTL_R &= ~(UART_CTL_UARTEN); // clears the uart control register

    UART1_IBRD_R = iBRD; // baud rate
    UART1_FBRD_R = fBRD;

    UART1_LCRH_R = UART_LCRH_WLEN_8; // set fram, 8 data bits, 1 stop bit, no parity, no FIFO
    UART1_CC_R = UART_CC_CS_SYSCLK; // set uart 1 to system clock

    UART1_CTL_R |= (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);    //re-enable uart 1 ctl


}

void uart_sendChar(char data){

    while(UART1_FR_R & UART_FR_TXFF){ // wait for room to send data
	   	}

UART1_DR_R = data; // sends the data
}

char uart_receive(void){

while(UART1_FR_R & UART_FR_RXFE){}
char data = (char) (UART1_DR_R & 0xFF);
return data;
}

void uart_sendStr(const char *data){
    //While not equal to null
        while(*data != '\0')
        {
            uart_sendChar(*data);
            data++;
        }
}
