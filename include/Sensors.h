#ifndef SENSORS_H_
#define SENSORS_H_

#include <Adafruit_LSM6DSO32.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BusIO_Register.h>
extern Adafruit_LSM6DSO32 imu;
extern sensors_event_t acc;
extern sensors_event_t gyro;
extern sensors_event_t temp;
void init_sensor();
#endif