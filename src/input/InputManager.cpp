#include "InputManager.h"
#include <Arduino.h>

static uint8_t potPin, upPin, downPin;
static int offsetC = 0;
static unsigned long lastUp = 0, lastDown = 0;
static bool previousUp = HIGH, previousDown = HIGH;

void InputManagerInit(uint8_t pot, uint8_t up, uint8_t down) {
    potPin = pot;
    upPin = up;
    downPin = down;

    pinMode(upPin, INPUT_PULLUP);
    pinMode(downPin, INPUT_PULLUP);
}

float InputManagerGetSetpoint() {
    const unsigned long now = millis();

    const bool upState = digitalRead(upPin);
    const bool downState = digitalRead(downPin);

    if (previousUp == HIGH && upState == LOW && now - lastUp > 180) {
        offsetC += 1;
        lastUp = now;
    }

    if (previousDown == HIGH && downState == LOW && now - lastDown > 180) {
        offsetC -= 1;
        lastDown = now;
    }

    previousUp = upState;
    previousDown = downState;

    const float potSetpoint = 20.0f + (analogRead(potPin) * 30.0f / 1023.0f);

    return constrain(potSetpoint + offsetC, 20.0f, 50.0f);
}