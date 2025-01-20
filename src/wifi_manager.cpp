#include "wifi_manager.h"

WiFiManager::WiFiManager(int statusLedPin) : _statusLedPin(statusLedPin) {
    pinMode(_statusLedPin, OUTPUT);
}

void WiFiManager::connect(const String& ssid, const String& password) {
    Serial.println("Trying to connect to Wi-Fi...");
    WiFi.begin(ssid.c_str(), password.c_str());

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        blinkLed(300);
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Wi-Fi Connected!");
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());
        setLed(true);
    } else {
        Serial.println("Failed to connect.");
        setLed(false);
    }
}

void WiFiManager::startAP(const char* apSSID, const char* apPassword) {
    IPAddress local_IP(4, 4, 4, 4);
    IPAddress gateway(4, 4, 4, 4);
    IPAddress subnet(255, 255, 255, 0);

    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP(apSSID, apPassword);
    Serial.print("Access Point started. Connect to: ");
    Serial.println(WiFi.softAPIP());
}

bool WiFiManager::isConnected() const {
    return WiFi.status() == WL_CONNECTED;
}

void WiFiManager::blinkLed(int delayValue) {
    digitalWrite(_statusLedPin, HIGH);
    delay(delayValue);
    digitalWrite(_statusLedPin, LOW);
    delay(delayValue);
}

void WiFiManager::setLed(bool state) {
    digitalWrite(_statusLedPin, state ? HIGH : LOW);
}