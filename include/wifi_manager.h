#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include <Arduino.h>

class WiFiManager {
public:
    WiFiManager(int statusLedPin);
    void connect(const String& ssid, const String& password);
    void startAP(const char* apSSID, const char* apPassword = nullptr);
    bool isConnected() const;
    void blinkLed(int delayValue);
    void setLed(bool state);
private:
    int _statusLedPin;
};

#endif