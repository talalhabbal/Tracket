#include "BLEFunctions.h"

BLEService sensorService(SERVICE_UUID);
BLECharacteristic dataChar(DATA_CHAR_UUID, BLERead | BLEWrite | BLENotify, PACKET_SIZE);

void setupBLE() {
    if(!BLE.begin()) {
        exit(1);
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
        float data[BUFFER_SIZE][SAMPLES_PER_READING];
        for(int i = 0; i < BUFFER_SIZE; i++) {
            data[i][0] = 100.0f;
            data[i][1] = 110.0f;
            data[i][2] = 120.0f;
        }
        dataChar.writeValue(data, sizeof(data));
    }
    BLE.advertise();
    delay(1000);
}