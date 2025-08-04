#ifndef SENSOR_H_
#define SENSOR_H_

#include <Arduino.h>
#include <Wire.h>
#define LSM6DSO32_ADDR 0x6A

#define STATUS_REG 0x1E

#define CTRL_3_C 0x12 // Reset
#define CTRL1_XL 0x10 // Acc control register
// #define CTRL6_C 0x15 // High performance ODR
#define CTRL9_XL 0x18
#define CTRL2_G 0x11 // Gyroscope control register
// #define CTRL7_G 0x16 // High performance ODR

#define OUTX_L_G 0x22

#define ACC_SCALE 0.00957f
#define GYRO_SCALE 0.00875f

typedef struct {
    float ax,ay,az;
    float gx,gy,gz;
} IMUData;

bool isDataReady();
bool readIMU(IMUData* data);
void initSensor();

#endif
