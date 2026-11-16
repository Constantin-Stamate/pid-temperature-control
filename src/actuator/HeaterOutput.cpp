#include "HeaterOutput.h"
#include <Arduino.h>

static uint8_t outputPin;

void HeaterOutputInit(uint8_t pwmPin) {
    outputPin = pwmPin;
    
    pinMode(outputPin, OUTPUT);
    analogWrite(outputPin, 0);
}

void HeaterOutputSet(int pwm) {
    analogWrite(outputPin, constrain(pwm, 0, 255));
}