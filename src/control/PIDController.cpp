#include "PIDController.h"
#include <Arduino.h>

static float Kp, Ki, Kd;
static float integral = 0.0f;
static float previousMeasurement = 0.0f;
static float outputMin = 0.0f, outputMax = 255.0f;
static float dtSeconds = 1.0f;
static bool firstRun = true;

void PIDControllerInit(float kp, float ki, float kd, unsigned long sampleMs) {
    Kp = kp;
    Ki = ki;
    Kd = kd;

    dtSeconds = sampleMs / 1000.0f;

    if (dtSeconds <= 0.0f) {
        dtSeconds = 1.0f;
    }

    integral = 0.0f;
    previousMeasurement = 0.0f;
    firstRun = true;
}

float PIDControllerCompute(float setPoint, float measuredValue) {
    const float error = setPoint - measuredValue;
    const float proportional = Kp * error;

    float derivative = 0.0f;

    if (!firstRun) {
        derivative = -(measuredValue - previousMeasurement) / dtSeconds;
    }

    previousMeasurement = measuredValue;
    firstRun = false;

    const float candidateIntegral = integral + error * dtSeconds;
    const float candidateOutput = proportional + Ki * candidateIntegral + Kd * derivative;

    if ((candidateOutput >= outputMin && candidateOutput <= outputMax) ||
        (candidateOutput > outputMax && error < 0.0f) ||
        (candidateOutput < outputMin && error > 0.0f)) {

        integral = constrain(candidateIntegral, -100.0f, 100.0f);
    }

    return constrain(proportional + Ki * integral + Kd * derivative,
                     outputMin, outputMax);
}