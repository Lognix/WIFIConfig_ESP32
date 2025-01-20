#include "web_server.h"

WebServerManager::WebServerManager() : server(80), _credentialsHandler(nullptr) {}

void WebServerManager::start() {
    server.on("/", std::bind(&WebServerManager::handleRoot, this));
    server.on("/connect", std::bind(&WebServerManager::handleConnect, this));
    server.begin();
    Serial.println("Web server started.");
}

void WebServerManager::handleClient() {
    server.handleClient();
}

void WebServerManager::setCredentialsHandler(void (*handler)(const String& ssid, const String& pass)) {
    _credentialsHandler = handler;
}

void WebServerManager::handleRoot() {
    server.send(200, "text/html",
                "<form action=\"/connect\" method=\"POST\">"
                "SSID: <input type=\"text\" name=\"ssid\"><br>"
                "PSWD: <input type=\"password\" name=\"pass\"><br>"
                "<input type=\"submit\" value=\"Connect\">"
                "</form>");
}

void WebServerManager::handleConnect() {
    String ssid = server.arg("ssid");
    String pass = server.arg("pass");

    if (_credentialsHandler) {
        _credentialsHandler(ssid, pass);
    }

    server.send(200, "text/html", "Connecting to Wi-Fi... Reload.");
}