#ifndef MOVE_H_
#define MOVE_H_

void turn_clockwise(oi_t *sensor, int degrees);


void move_forward(oi_t *sensor, int centi);

void turn_counterclockwise(oi_t *sensor_data, int degrees);

int sum_move_forward(oi_t *sensor_data, int centi, double* sum);

#endif
