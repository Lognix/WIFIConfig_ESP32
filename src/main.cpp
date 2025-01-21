#include <Arduino.h>
#include "wifi_manager.h"
#include "web_server.h"
#include "nvs_manager.h"
#include "pins_manager.h"
#include "pins_config.h"

const char *ssid_ap = "CONFIGURATION";
const char *password_ap = "12345678";

WiFiManager wifiManager; 
WebServerManager webServer; 
NVSManager nvsManager;
PinsManager statusLED(STATUS_LED_PIN, OUTPUT);

void handleCredentials(const String& ssid, const String& pass) {
    nvsManager.saveData("ssid", ssid.c_str());
    nvsManager.saveData("pass", pass.c_str());
    nvsManager.saveData("last", "true");
    delay(1000);
    ESP.restart();
}

void checkLastConnection() {
    String last = nvsManager.readData("last");
    if (last == "true") {
        String ssid = nvsManager.readData("ssid");
        String pass = nvsManager.readData("pass");
        delay(100);
        wifiManager.connect(ssid, pass);
    } else {
        wifiManager.startAP(ssid_ap, password_ap);
        webServer.setCredentialsHandler(handleCredentials);
        webServer.start();
        while(!wifiManager.isConnected()) {
            webServer.handleClient();
            statusLED.blinkLed(150);
        }
    }
}


void setup() {
    Serial.begin(115200);
    checkLastConnection();
}

void loop() {
    
}