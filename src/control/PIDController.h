#pragma once

void PIDControllerInit(float kp, float ki, float kd, unsigned long sampleMs);
float PIDControllerCompute(float setPoint, float measuredValue);