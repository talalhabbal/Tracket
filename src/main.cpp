#include <Arduino.h>
#include "BLEFunctions.h"

int main() {
    Serial.begin(115200);
    setupBLE();
    while(!BLE.connected()) {
        BLE.advertise();
        delay(1000);
    }
    while(1) {
        runBLEService();
    }
    return 0;
}