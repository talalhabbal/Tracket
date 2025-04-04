#include <Arduino.h>
#include "BLEFunctions.h"
#include "Led.h"
#include "Sensors.h"

int main() {
    Serial.begin(115200);
    setupBLE();
    init_led();
    init_sensor();
    setYellowLED();
    
    while(!BLE.connected()) {
        BLE.advertise();
        setYellowLED();
        delay(1000);
    }
    while(1) {
        runBLEService();
        setGreenLED();
    }
    return 0;
}