#include "Sensors.h"
Adafruit_LSM6DSO32 imu;
sensors_event_t acc;
sensors_event_t gyro;
sensors_event_t temp;

/// @brief Initialization of the adafruit LSM6DSO32 imu.
/// Range and datarate of accelerometer and gyroscope are initialized here
/// @return returns 1 if I2C set up fails.
void init_sensor() {
    if(!imu.begin_I2C()) {
        // Add LED code to turn red if an error occurred.
    }

    imu.setAccelRange(LSM6DSO32_ACCEL_RANGE_32_G);
    imu.setGyroRange(LSM6DS_GYRO_RANGE_1000_DPS);
    imu.setAccelDataRate(LSM6DS_RATE_1_66K_HZ);
    imu.setGyroDataRate(LSM6DS_RATE_1_66K_HZ);
}