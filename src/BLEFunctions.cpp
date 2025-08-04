#include "BLEFunctions.h"
#include "Sensor.h"

BLEService sensorService(SERVICE_UUID);
BLECharacteristic dataChar(DATA_CHAR_UUID, BLERead | BLEWrite | BLENotify, PACKET_SIZE);

float dataBuffer1[BUFFER_SIZE][READINGS_PER_SAMPLE];
float dataBuffer2[BUFFER_SIZE][READINGS_PER_SAMPLE];

float(*currentBuffer)[READINGS_PER_SAMPLE] = dataBuffer1;
float(*sendBuffer)[READINGS_PER_SAMPLE] = dataBuffer2;

int sendBufferSize = 0;

/// @brief Set up initial bluetooth connection. This function sets the name of the bluetooth when advertising
/// and adds the characteristics to the bluetooth service. Bluetooth then adds that service with the
/// attached  characteristics to be advertised. A connection interval of 5-7.5ms is specified. The BLE then starts
/// advertising.
void setupBLE() {
    if(!BLE.begin()) {
    }
    BLE.setLocalName("Nano33BLE"); // Set name to Nano33BLE
    sensorService.addCharacteristic(dataChar); // Add Characteristic to service
    BLE.addService(sensorService); // Add service to BLE
    BLE.setAdvertisedService(sensorService); // Set the advertised service to the chosen service
    BLE.setConnectionInterval(5, 7.5);
    BLE.advertise(); // Start advertising
}

/// @brief Runs the BLE communication. A central connection is created and while it is connected,
/// The sensor readings are taken and stored in a buffer to be transmitted over BLE to the peripheral device.
/// If the connection drops at any point, the BLE service starts advertising again.
void runBLEService() {
    BLEDevice central = BLE.central();
    unsigned long startTime = millis();
    unsigned long timeout = 15000;
    while (central.connected() && !dataChar.subscribed() && millis() - startTime < timeout) {
        delay(10);  // Let BLE stack finish GATT negotiation
    }
    while(central.connected()) {
        int i = 0;
        while(i < BUFFER_SIZE) {
            if(isDataReady()) {
                IMUData data;
                if(readIMU(&data)) {
                    currentBuffer[i][0] = data.ax;
                    currentBuffer[i][1] = data.ay;
                    currentBuffer[i][2] = data.az;
                    currentBuffer[i][3] = data.gx;
                    currentBuffer[i][4] = data.gy;
                    currentBuffer[i][5] = data.gz;
                    i++;
                }
            }
        }

        float(*temp)[READINGS_PER_SAMPLE] = currentBuffer;
        currentBuffer = sendBuffer;
        sendBuffer = temp;
        sendBufferSize = i;

        if(sendBufferSize > 0) {
            dataChar.writeValue(sendBuffer, PACKET_SIZE);
            sendBufferSize = 0;
            delay(3);
        }
    }
    BLE.advertise();
    delay(1000);
}