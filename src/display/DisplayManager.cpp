#include "DisplayManager.h"
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

static LiquidCrystal_I2C lcd(0x27, 16, 2);

void DisplayManagerInit() {
    lcd.init();
    lcd.backlight();
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("PID Temperature");

    lcd.setCursor(0, 1);
    lcd.print("Initializing...");

    delay(800);
}

void DisplayManagerShow(float setPoint, float temperature, int pwm) {
    lcd.setCursor(0, 0);
    lcd.print("SP:");
    lcd.print(setPoint, 1);
    lcd.print("C PV:");
    lcd.print(temperature, 1);
    lcd.print("  ");

    lcd.setCursor(0, 1);
    lcd.print("PWM:");
    lcd.print(pwm);
    lcd.print(" ");
    lcd.print((pwm * 100) / 255);
    lcd.print("%       ");
}

void DisplayManagerShowError() {
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("SENSOR ERROR!");

    lcd.setCursor(0, 1);
    lcd.print("Check DS18B20");
}