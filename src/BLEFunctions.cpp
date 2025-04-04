#include "BLEFunctions.h"
#include <Arduino_BMI270_BMM150.h>
#include "Led.h"
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
            data[i][0] = 100.0f;
            data[i][1] = 110.0f;
            data[i][2] = 120.0f;
            data[i][3] = 10.0f;
            data[i][4] = 20.0f;
            data[i][5] = 30.0f;
            delay(READINGS_DELAY);
        }
        dataChar.writeValue(data, sizeof(data));
    }
    BLE.advertise();
    setYellowLED();
    delay(1000);
}