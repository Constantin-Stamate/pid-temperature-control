#include "TemperatureSensor.h"
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

static OneWire* oneWireBus = nullptr;
static DallasTemperature* temperatureSensor = nullptr;

void TemperatureSensorInit(uint8_t dataPin) {
    oneWireBus = new OneWire(dataPin);
    temperatureSensor = new DallasTemperature(oneWireBus);

    temperatureSensor->begin();
}

float TemperatureSensorReadC() {
    if (temperatureSensor == nullptr) {
        return DEVICE_DISCONNECTED_C;
    }

    temperatureSensor->requestTemperatures();

    return temperatureSensor->getTempCByIndex(0);
}