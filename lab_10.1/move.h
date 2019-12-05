#ifndef MOVE_H_
#define MOVE_H_

void turn_clockwise(oi_t *sensor, int degrees);

void bot_init(void);

void move_forward(oi_t *sensor, int centi);

void turn_counterclockwise(oi_t *sensor_data, int degrees);

int sum_move_forward(oi_t *sensor_data, int centi, double* sum);
void line_detect(oi_t *sensor_data);
void cliff_detect(oi_t *sensor_data);


#endif