#include <Arduino.h>
#include "wifi_manager.h"
#include "web_server.h"
#include "nvs_manager.h"

const char *ssid_ap = "CONFIGURATION";
const char *password_ap = "12345678";
const int statusLed = 13;

WiFiManager wifiManager(statusLed);
WebServerManager webServer;
NVSManager nvsManager;

void handleCredentials(const String& ssid, const String& pass) {
    nvsManager.saveData("ssid", ssid.c_str());
    nvsManager.saveData("pass", pass.c_str());
    nvsManager.saveData("last", "true");
    ESP.restart();
}

void setup() {
    Serial.begin(115200);

    String ssid = nvsManager.readData("ssid");
    String pass = nvsManager.readData("pass");
    String last = nvsManager.readData("last");

    Serial.println("Last connecting status: " + last);
    Serial.println("SSID: " + ssid);
    Serial.println("PSWD: " + pass);

    if (last == "true") {
        wifiManager.connect(ssid, pass);
    } else {
        wifiManager.startAP(ssid_ap, password_ap);
        webServer.setCredentialsHandler(handleCredentials);
        webServer.start();
    }
}

void loop() {
    if (!wifiManager.isConnected()) {
        webServer.handleClient();
        wifiManager.blinkLed(250);
    }
}