ESP32 Wi-Fi Configuration with Web Interface
  This project is a firmware for the ESP32 that allows configuring Wi-Fi connectivity via a web interface. If the device cannot connect to a saved Wi-Fi network, it automatically starts an access point (AP) with a web page for configuring new Wi-Fi credentials.

Features
  Automatic Wi-Fi Connection: The device attempts to connect to a saved Wi-Fi network on startup.
  Access Point (AP) Mode: If the Wi-Fi connection fails, the ESP32 starts an access point with the name CONFIGURATION and the password 12345678.
  Web Interface for Configuration: Users can connect to the access point and open a web page to enter the SSID and password of a new Wi-Fi network.
  Settings Storage: The entered data is saved in non-volatile storage (NVS) and used for reconnection after a reboot.
  Status Indication: An LED on pin 13 is used to indicate the status (blinking in AP mode, steady light when successfully connected to Wi-Fi).

Project Structure
  WIFIConfig_ESP32/
  ├── include/               # Header files
  │   ├── config.h           # Pin and parameter configuration
  │   ├── pins_manager.h     # LED and pin management
  │   ├── wifi_manager.h     # Wi-Fi and access point management
  │   ├── web_server.h       # Web server for Wi-Fi configuration
  │   └── nvs_manager.h      # Non-volatile storage (NVS) management
  ├── src/                   # Source code
  │   ├── main.cpp           # Main program file
  │   ├── pins_manager.cpp   # Pin management implementation
  │   ├── wifi_manager.cpp   # Wi-Fi management implementation
  │   ├── web_server.cpp     # Web server implementation
  │   └── nvs_manager.cpp    # NVS management implementation
  ├── platformio.ini         # PlatformIO configuration
  └── README.md              # Project description

Libraries Used
- WiFi: For Wi-Fi and access point functionality.
- WebServer: For creating the web interface.
- NVS (Non-Volatile Storage): For saving Wi-Fi settings in non-volatile memory.


Wi-Fi Configuration:
  If the ESP32 cannot connect to a Wi-Fi network, it will start an access point with the name CONFIGURATION and the password 12345678.
  Connect to this access point and open a web browser.
  Enter the SSID and password of your Wi-Fi network on the web page.
  After saving the settings, the ESP32 will reboot and attempt to connect to the specified network.
Usage Example
  After uploading the firmware, the ESP32 will attempt to connect to a saved Wi-Fi network.
  If the connection fails, the LED on pin 13 will start blinking, and the ESP32 will start an access point.
  Connect to the CONFIGURATION access point and open the web page at 4.4.4.4.
  Enter the SSID and password of your Wi-Fi network.
  After saving the settings, the ESP32 will reboot and connect to the specified network.
