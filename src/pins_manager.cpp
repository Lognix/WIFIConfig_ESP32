#include <pins_manager.h>

PinsManager::PinsManager(int pin, int mode) : _pin(pin) {
    pinMode(_pin, mode);
}

void PinsManager::blinkLed(int delayValue) {
    digitalWrite(_pin, HIGH);
    delay(delayValue);
    digitalWrite(_pin, LOW);
    delay(delayValue);
}

void PinsManager::setLed(bool state) {
    digitalWrite(_pin, state ? HIGH : LOW);
}