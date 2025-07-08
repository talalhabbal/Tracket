#include <Arduino.h>
#include "Led.h"

/// @brief Initializes LED pins to output. Arduino core is initialized in this function
/// For timers and interrupts to be used.
void init_led() {
    init();
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
}
/// @brief Turn the LED red
void setRedLED() {
    analogWrite(RED_PIN, 255);
    analogWrite(GREEN_PIN, 0);
    analogWrite(BLUE_PIN, 0);
}
/// @brief Turn the LED yellow
void setYellowLED() {
    analogWrite(RED_PIN, 255);
    analogWrite(GREEN_PIN, 255);
    analogWrite(BLUE_PIN, 0);
}

/// @brief Turn the LED green
void setGreenLED() {
    analogWrite(RED_PIN, 0);
    analogWrite(GREEN_PIN, 255);
    analogWrite(BLUE_PIN, 0);
}