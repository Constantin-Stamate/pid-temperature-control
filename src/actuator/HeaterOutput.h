#pragma once

#include <stdint.h>

void HeaterOutputInit(uint8_t pwmPin);
void HeaterOutputSet(int pwm);