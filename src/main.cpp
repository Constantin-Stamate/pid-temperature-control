#include <Arduino.h>

#include "control/PIDController.h"
#include "display/DisplayManager.h"
#include "input/InputManager.h"
#include "sensor/TemperatureSensor.h"
#include "actuator/HeaterOutput.h"

constexpr uint8_t TEMP_PIN = 8;
constexpr uint8_t POT_PIN = A0;
constexpr uint8_t BTN_UP = 4;
constexpr uint8_t BTN_DOWN = 5;
constexpr uint8_t HEATER_PWM_PIN = 10;

constexpr unsigned long SAMPLE_MS = 1000;

void setup() {
    Serial.begin(9600);

    TemperatureSensorInit(TEMP_PIN);
    InputManagerInit(POT_PIN, BTN_UP, BTN_DOWN);
    DisplayManagerInit();
    HeaterOutputInit(HEATER_PWM_PIN);

    PIDControllerInit(18.0, 0.8, 2.0, SAMPLE_MS);

    Serial.println(F("SetPoint_C\tTemperature_C\tOutput_PWM"));
}

void loop() {
    static unsigned long lastSample = 0;

    const unsigned long now = millis();

    if (now - lastSample >= SAMPLE_MS) {
        lastSample = now;

        const float setPoint = InputManagerGetSetpoint();
        const float temperature = TemperatureSensorReadC();

        if (temperature < -50.0f || temperature > 125.0f) {
            HeaterOutputSet(0);
            DisplayManagerShowError();

            Serial.println(F("0\t0\t0"));

            return;
        }

        const float output = PIDControllerCompute(setPoint, temperature);

        const int pwm = constrain((int)(output + 0.5f), 0, 255);

        HeaterOutputSet(pwm);
        DisplayManagerShow(setPoint, temperature, pwm);

        Serial.print(setPoint, 1);
        Serial.print('\t');

        Serial.print(temperature, 1);
        Serial.print('\t');

        Serial.println(pwm);
    }
}