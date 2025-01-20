ESP32 Wi-Fi Configuration with Web Interface
  
  This project is a firmware for the ESP32 that allows configuring Wi-Fi connectivity via a web interface. If the device cannot connect to a saved Wi-Fi network, it automatically starts an access point (AP) with a web page for configuring new Wi-Fi credentials.
  
Libraries Used

- WiFi: For Wi-Fi and access point functionality.
- WebServer: For creating the web interface.
- NVS (Non-Volatile Storage): For saving Wi-Fi settings in non-volatile memory.

Usage Example

  After uploading the firmware, the ESP32 will attempt to connect to a saved Wi-Fi network.
  If the connection fails, the LED on pin 13 will start blinking, and the ESP32 will start an access point.
  Connect to the CONFIGURATION access point and open the web page at 4.4.4.4.
  Enter the SSID and password of your Wi-Fi network.
  After saving the settings, the ESP32 will reboot and connect to the specified network.
