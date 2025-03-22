#ifndef BLEFUNCTIONS_H_
#define BLEFUNCTIONS_H_

#include <ArduinoBLE.h>

#define SERVICE_UUID        "12345678-1234-1234-1234-123456789ABC"
#define DATA_CHAR_UUID      "12345678-1234-1234-1234-123456789AB1"
#define PACKET_SIZE         (BUFFER_SIZE * 12) // 12 Bytes of data 
#define BUFFER_SIZE         15 // 15 Samples before sending a packet
#define READINGS_DELAY      1
#define SAMPLES_PER_READING 3

void setupBLE();
void runBLEService();

#endif