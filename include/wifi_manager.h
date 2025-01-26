#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include <Arduino.h>

class WiFiManager {
public:
    WiFiManager();
    void connect(const char* ssid, const char* password);
    void startAP(const char* apSSID, const char* apPassword = nullptr);
    bool isConnected() const;
    void blinkLed(int delayValue);
    void setLed(bool state);
private:

};

#endif