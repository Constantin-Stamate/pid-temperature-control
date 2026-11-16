#pragma once

#include <stdint.h>

void TemperatureSensorInit(uint8_t dataPin);
float TemperatureSensorReadC();