#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <WebServer.h>
#include <Arduino.h>

class WebServerManager {
public:
    WebServerManager();
    void startSetupSrv();
    void startWebSrv();
    void handleHeap();
    void setWebPage();
    void handleClient();
    void setCredentialsHandler(void (*handler)(const String& ssid, const String& pass));
private:
    WebServer server;
    void handleRoot();
    void handleConnect();
    void (*_credentialsHandler)(const String& ssid, const String& pass);
};

#endif