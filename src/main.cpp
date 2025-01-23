#include <Arduino.h>
#include "wifi_manager.h"
#include "web_server.h"
#include "nvs_manager.h"
#include "pins_manager.h"
#include "pins_config.h"

const char *ssid_ap = "CONFIGURATION";
const char *password_ap = "12345678";

NVSManager nvsManager;
WebServerManager webServer; 

void handleCredentials(const String& ssid, const String& pass) {
    nvsManager.saveData("ssid", ssid.c_str());
    nvsManager.saveData("pass", pass.c_str());
    nvsManager.saveData("last", "true");
    delay(1000);
    ESP.restart();
}


void checkLastConnection() {
    WiFiManager wifiManager; 
    PinsManager statusLED(STATUS_LED_PIN, OUTPUT);

    String last = nvsManager.readData("last");
    if (last == "true") {
        String ssid = nvsManager.readData("ssid");
        String pass = nvsManager.readData("pass");
        delay(10);
        wifiManager.connect(ssid, pass);
    } else {
        wifiManager.startAP(ssid_ap, password_ap);
        webServer.setCredentialsHandler(handleCredentials);
        webServer.startSetupSrv();
        while(!wifiManager.isConnected()) {
            webServer.handleClient();
            statusLED.blinkLed(150);
        }
    }
}


void setup() {
    Serial.begin(115200);
    Serial.printf("Flash size: %d kB\n", ESP.getFlashChipSize()/1024);
    Serial.printf("PSRAM size: %d kB\n", ESP.getPsramSize()/1024);
    Serial.printf("Heap: %d kB\n", ESP.getHeapSize()/1024);
    Serial.printf("Free heap: %d kB\n", ESP.getFreeHeap()/1024);
    checkLastConnection();
    webServer.startWebSrv();
}

void loop() {
    webServer.handleClient();
}