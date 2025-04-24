#include <Arduino.h>
#include "BLEFunctions.h"
#include "Led.h"
#include "Sensors.h"

/// @brief Entry point of the program, initialization of the sensors and bluetooth
/// is handled in this function. BLE communication and sensor reading occurs if
/// BLE is connected, otherwise it stays in advertising mode.
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