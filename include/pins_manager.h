#ifndef PINS_MANAGER_H
#define PINS_MANAGER_H

#include <Arduino.h>

class PinsManager {
public:
    PinsManager(int pin, int mode = OUTPUT);
    void blinkLed(int delayValue);
    void setLed(bool state);
private:
    int _pin;
};

#endif