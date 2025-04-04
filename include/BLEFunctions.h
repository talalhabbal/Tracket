#ifndef BLEFUNCTIONS_H_
#define BLEFUNCTIONS_H_

#include <ArduinoBLE.h>

#define SERVICE_UUID        "12345678-1234-1234-1234-123456789ABC"
#define DATA_CHAR_UUID      "12345678-1234-1234-1234-123456789AB1"
#define PACKET_SIZE         BUFFER_SIZE * READINGS_PER_SAMPLE * 4 // 4 Bytes (Float) * 6 Readings * Buffer size
#define BUFFER_SIZE         10 // 15 Samples before sending a packet
#define READINGS_DELAY      100 // Delay between each reading
#define READINGS_PER_SAMPLE 6 // 6 Readings total from 2 sensors (ax, ay, az, gx, gy, gz)

void setupBLE();
void runBLEService();

#endif