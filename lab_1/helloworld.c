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


#include "open_interface.h"
void main() {
 oi_t *sensor_data = oi_alloc();
 oi_init(sensor_data);
 double sum = 0;
 oi_setWheels(500, 500); // move forward; full speed
 while (sum < 1000) {
 oi_update(sensor_data);
 sum += sensor_data->distance;
 }
 oi_setWheels(0, 0); // stop
 oi_free(sensor_data);
