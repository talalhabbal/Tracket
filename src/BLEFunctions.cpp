#include "BLEFunctions.h"
#include "Led.h"
#include "Sensors.h"
BLEService sensorService(SERVICE_UUID);
BLECharacteristic dataChar(DATA_CHAR_UUID, BLERead | BLEWrite | BLENotify, PACKET_SIZE);

void setupBLE() {
    if(!BLE.begin()) {
        setRedLED();
    }

    BLE.setLocalName("Nano33BLE"); // Set name to Nano33BLE
    sensorService.addCharacteristic(dataChar); // Add Characteristic to service
    BLE.addService(sensorService); // Add service to BLE
    BLE.setAdvertisedService(sensorService); // Set the advertised service to the chosen service
    BLE.setConnectionInterval(5, 7.5);
    BLE.advertise(); // Start advertising
}

void runBLEService() {
    BLEDevice central = BLE.central();
    while(central.connected()) {
        float data[BUFFER_SIZE][READINGS_PER_SAMPLE];
        for(int i = 0; i < BUFFER_SIZE; i++) {
            imu.getEvent(&acc, &gyro, &temp);
            data[i][0] = acc.acceleration.x;
            data[i][1] = acc.acceleration.y;
            data[i][2] = acc.acceleration.z;
            data[i][3] = gyro.gyro.x;
            data[i][4] = gyro.gyro.y;
            data[i][5] = gyro.gyro.z;
            delay(READINGS_DELAY);
        }
        dataChar.writeValue(data, sizeof(data));
    }
    BLE.advertise();
    setYellowLED();
    delay(1000);
}