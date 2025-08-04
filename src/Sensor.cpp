#include "Sensor.h"

void initSensor() {
    Wire.begin();
    // Wire.setClock(400000);

    Wire.beginTransmission(LSM6DSO32_ADDR);
    Wire.write(CTRL_3_C);
    Wire.write(0x01);
    Wire.endTransmission();
    delay(100);

    Wire.beginTransmission(LSM6DSO32_ADDR);
    Wire.write(CTRL1_XL);
    Wire.write(0b01010100);
    Wire.endTransmission();
    // CTRL9_XL – Enable accelerometer axes (default enabled, but just in case)
    Wire.beginTransmission(LSM6DSO32_ADDR);
    Wire.write(CTRL9_XL);
    Wire.write(0b111);  // Enable X, Y, Z
    Wire.endTransmission();

    Wire.beginTransmission(LSM6DSO32_ADDR);
    Wire.write(CTRL2_G);
    Wire.write(0b01010000);
    Wire.endTransmission();
}

bool isDataReady() {
    Wire.beginTransmission(LSM6DSO32_ADDR);
    Wire.write(STATUS_REG);
    if (Wire.endTransmission(false) != 0) {
        return false;
    }
    Wire.requestFrom(LSM6DSO32_ADDR, 1);
    if (Wire.available()) {
        uint8_t status = Wire.read();
        return (status & 0b00000011) == 0b00000011; // accel and gyro data ready
    }
    return false;
}

bool readIMU(IMUData* data) {
    uint8_t raw[12];

    Wire.beginTransmission(LSM6DSO32_ADDR);
    Wire.write(OUTX_L_G);
    if (Wire.endTransmission(false) != 0) return false;
    Wire.requestFrom(LSM6DSO32_ADDR, 12);
    if (Wire.available() < 12) return false; 
    for (int i = 0; i < 12 && Wire.available(); i++) {
    raw[i] = Wire.read();
    }
    
    int16_t gx = (int16_t)(raw[0] | (raw[1] << 8));
    int16_t gy = (int16_t)(raw[2] | (raw[3] << 8));
    int16_t gz = (int16_t)(raw[4] | (raw[5] << 8));

    int16_t ax = (int16_t)(raw[6] | (raw[7] << 8));
    int16_t ay = (int16_t)(raw[8] | (raw[9] << 8));
    int16_t az = (int16_t)(raw[10] | (raw[11] << 8));

    data->gx = gx * GYRO_SCALE;
    data->gy = gy * GYRO_SCALE;
    data->gz = gz * GYRO_SCALE;

    data->ax = ax * ACC_SCALE;
    data->ay = ay * ACC_SCALE;
    data->az = az * ACC_SCALE;

    return true;
}