#include <timer.h>
#include "lcd.h"
#include "driverlib/interrupt.h"
#include "servo.h"
#include "button.h"



int main(void){
    timer1_init();
    button_init();
    lcd_init();
    int y = 0;
    int degrees = 90;
    int direction = 1; //1 for clockwise -1 for counterclockwise
    move_servo(90);
    while(1){
        lcd_printf("Degree: %d  Dir: %d", degrees, direction);

        while(y==0){ // waits for button press

            y= button_getButton();
            timer_waitMillis(150); // prevents multiple button presses

        }

        if (y ==4){
            if (direction==-1){ //moves servo to 180 degrees when in counterclockwise mode
                degrees = 180;
                move_servo(degrees);

            }
            if (direction ==1){ //moves servo to 0 degrees when in clockwise mode
                degrees = 0;
                move_servo(degrees);

            }
            y=0;
        }

        if (y ==3){ // switches between direction modes (clockwise/counterclockwise)
            direction = direction*(-1);
            y=0;
        }

        if (y ==2){ //moves servo 5 degrees
            degrees = degrees + 5*direction;
            move_servo(degrees);

            y=0;
        }

        if (y ==1){ //moves servo 1 degree
            degrees = degrees + 1*direction;
            move_servo(degrees);
            y=0;
        }


    }

}



