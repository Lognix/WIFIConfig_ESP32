#include <Arduino.h>
#include "wifi_manager.h"
#include "web_server.h"
#include "nvs_manager.h"
#include "pins_manager.h"
#include "pins_config.h"
#include "config.h"
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>




NVSManager nvsManager;
WebServerManager webServer; 

WiFiClientSecure client;
UniversalTelegramBot bot(TGTOKEN, client);

long lastUpdateId = 0;

void handleCredentials(const char* ssid, const char* pass) {
    nvsManager.saveData("ssid", ssid);
    nvsManager.saveData("pass", pass);
    nvsManager.saveData("last", "true");
    delay(500);
    ESP.restart();
}


void checkLastConnection() {
    WiFiManager wifiManager; 
    PinsManager statusLED(STATUS_LED_PIN, OUTPUT);

    String last = nvsManager.readData("last");
    if (last == "true") {
        String ssid = nvsManager.readData("ssid");
        String pass = nvsManager.readData("pass");
        delay(100);
        wifiManager.connect(ssid.c_str(), pass.c_str());
    } else {
        wifiManager.startAP(SSID_AP, PASS_AP);
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
    client.setInsecure();
}

void loop() {
    webServer.handleClient();
    int numNewMessages = bot.getUpdates(lastUpdateId);
  while (numNewMessages) {
    Serial.println("New message received!");

    for (int i = 0; i < numNewMessages; i++) {
      String chat_id = bot.messages[i].chat_id;
      String text = bot.messages[i].text;
      String from_name = bot.messages[i].from_name;

      if (from_name == "") from_name = "Unknown";

      Serial.println("From: " + from_name);
      Serial.println("Chat ID: " + chat_id);
      Serial.println("Message: " + text);

      bot.sendMessage(chat_id, "You said: " + text, "");

      lastUpdateId = bot.messages[i].update_id + 1;
    }

    numNewMessages = bot.getUpdates(lastUpdateId);
  }

  delay(1000); 
}