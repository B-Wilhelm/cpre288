

#include "Timer.h"
#include "lcd.h"
#include "open_interface.h"
#include "move.h"




void main() {




    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    move_forward(sensor_data, 1900);


}



















	// lcd_puts("Hello, world");// Replace lcd_printf with lcd_puts
                                 // step through in debug mode
                                 // and explain to TA how it
                                 // works


    
	// NOTE: It is recommended that you use only lcd_init(), lcd_printf(), lcd_putc, and lcd_puts from lcd.h.
    // NOTE: For time fuctions see Timer.h


