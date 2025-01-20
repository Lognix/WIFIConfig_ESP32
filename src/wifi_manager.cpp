#include "wifi_manager.h"
#include "pins_manager.h"
#include "pins_config.h"
#include "nvs_manager.h"

PinsManager WIFIStatusLED(STATUS_LED_PIN, OUTPUT);
NVSManager save;



WiFiManager::WiFiManager() {
}

void WiFiManager::connect(const String& ssid, const String& password) {
    Serial.println("Trying to connect to Wi-Fi...");
    WiFi.begin(ssid.c_str(), password.c_str());

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        WIFIStatusLED.blinkLed(300);
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Wi-Fi Connected!");
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());
        save.saveData("last", "true");
        WIFIStatusLED.setLed(true);
    } else {
        Serial.println("Failed to connect.");
        WIFIStatusLED.setLed(false);
        save.saveData("last", "false");
        //startAP("CONFIGURATION", "12345678");
        //ESP.restart();
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