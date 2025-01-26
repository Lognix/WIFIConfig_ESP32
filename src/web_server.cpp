#include "web_server.h"
#include "html_content.h"

WebServerManager::WebServerManager() : server(80), _credentialsHandler(nullptr) {}

void WebServerManager::startSetupSrv() {
    server.on("/", std::bind(&WebServerManager::handleRoot, this));
    server.on("/connect", std::bind(&WebServerManager::handleConnect, this));
    server.begin();
    Serial.println("Web server started.");
}


void WebServerManager::startWebSrv() {
    server.on("/", std::bind(&WebServerManager::setWebPage, this));
    server.on("/heap", std::bind(&WebServerManager::handleHeap, this));
    server.begin();
    Serial.println("Web server started.");
}


void WebServerManager::handleHeap() {
    server.send(200, "text/plain", String(ESP.getFreeHeap()) + " B\nTemp: " + String(temperatureRead()));
}

void WebServerManager::setWebPage() {
    server.send(200, "text/html", HTML_INDEX);
}


void WebServerManager::handleClient() {
    server.handleClient();
}

void WebServerManager::setCredentialsHandler(void (*handler)(const char* ssid, const char* pass)) {
    _credentialsHandler = handler;
}

void WebServerManager::handleRoot() {
    server.send(200, "text/html", HTML_SETUP);
}

void WebServerManager::handleConnect() {
    String ssid = server.arg("ssid");
    String pass = server.arg("pass");

    if (_credentialsHandler) {
        _credentialsHandler(ssid.c_str(), pass.c_str());
    }

    server.send(200, "text/html", "Connecting to Wi-Fi... Reload.");
}