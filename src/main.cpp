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





// #include <Arduino.h>
// #include <WiFi.h>
// #include <WebServer.h>
// #include <nvs_flash.h>
// #include <nvs.h>

// const char *ssid_ap = "CONFIGURATION";
// const char *password_ap = "12345678";
// String ssid = "";
// String pass = "";
// String last = "false";
// const int statusLed = 13;
// WebServer server(80);


// void cfg_pins() {
//   pinMode(statusLed, OUTPUT);
// }

// void nvs_saveData(const char* key, const char* value) {
//   nvs_handle_t nvs_handle;
//   esp_err_t err;
//   err = nvs_open("storage", NVS_READWRITE, &nvs_handle);
//   err = nvs_set_str(nvs_handle, key, value);
//   err = nvs_commit(nvs_handle);
//   nvs_close(nvs_handle);
// }

// String nvs_readData(const char* key) {
//   static char value[256];
//   size_t len = sizeof(value);
//   nvs_handle_t nvs_handle;
//   esp_err_t err = nvs_open("storage", NVS_READONLY, &nvs_handle);
//   err = nvs_get_str(nvs_handle, key, value, &len);
//   nvs_close(nvs_handle);
//   if (err == ESP_OK) {
//     return String(value);
//   } else {
//     return "";
//   }
// }

// void led_blink(int devayValue) {
//     digitalWrite(statusLed, HIGH);
//     delay(devayValue);
//     digitalWrite(statusLed, LOW);
//     delay(devayValue);
// }

// void led_on(bool state, int pin) {
//   if (state)
//     digitalWrite(pin, HIGH);
//   else
//     digitalWrite(pin, LOW);
// }

// void connect_toWiFi() {
//   Serial.println("Try to connect to Wi-Fi...");
//   WiFi.begin(ssid.c_str(), pass.c_str());

//   int i = 0;
//   while (WiFi.status() != WL_CONNECTED && i < 20) {
//     led_blink(300);
//     i++;
//   }

//   if (WiFi.status() == WL_CONNECTED) {
//     Serial.println("Wi-Fi Connected!");
//     Serial.print("IP: ");
//     Serial.println(WiFi.localIP());
//     nvs_saveData("last", "true");
//     led_on(true, statusLed);
//   } else {
//     Serial.println("Cannot connected.");
//     nvs_saveData("last", "false");
//     ESP.restart();
//   }
// }

// void cfg_startAP() {
//   IPAddress local_IP(4, 4, 4, 4);
//   IPAddress gateway(4, 4, 4, 4);
//   IPAddress subnet(255, 255, 255, 0);

//   WiFi.softAPConfig(local_IP, gateway, subnet);
//   WiFi.softAP(ssid_ap, password_ap);
//   Serial.print("Access point startet. Connect to: ");
//   Serial.println(WiFi.softAPIP());

//   server.on("/", []() {
//     server.send(200, "text/html",
//                 "<form action=\"/connect\" method=\"POST\">"
//                 "SSID: <input type=\"text\" name=\"ssid\"><br>"
//                 "PSWD: <input type=\"password\" name=\"pass\"><br>"
//                 "<input type=\"submit\" value=\"Connect\">"
//                 "</form>");
//   });

//   server.on("/connect", []() {
//     String ssidFW = server.arg("ssid");
//     String passFW = server.arg("pass");

//     nvs_saveData("ssid", ssidFW.c_str());
//     nvs_saveData("pass", passFW.c_str());
//     nvs_saveData("last", "true");

//     ssid = ssidFW;
//     pass = passFW;
//     last = "true";

//     server.send(200, "text/html", "Connecting to Wi-Fi... Reload.");
//     ESP.restart();
//   });

//   server.begin();

//   while(true) {
//     server.handleClient();
//     led_blink(250);
//   }
// }

// void cfg_strings() {
//   ssid = nvs_readData("ssid");
//   pass = nvs_readData("pass");
//   last = nvs_readData("last");
// }

// void setup() {

//   Serial.begin(115200);

//   cfg_pins();

//   esp_err_t err = nvs_flash_init();

//   cfg_strings();

//   Serial.println("Last connecting status: " + last);
//   Serial.println("SSID: " + ssid);
//   Serial.println("PSWD: " + pass);

//   if (last == "true") {
//     connect_toWiFi();
//   } else {
//     cfg_startAP();
//   }
// }

// void loop() {
  
// }