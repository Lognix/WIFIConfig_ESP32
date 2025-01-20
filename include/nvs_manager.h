#ifndef NVS_MANAGER_H
#define NVS_MANAGER_H

#include <nvs_flash.h>
#include <nvs.h>
#include <Arduino.h>

class NVSManager {
public:
    NVSManager();
    bool saveData(const char* key, const char* value);
    String readData(const char* key);
private:
    nvs_handle_t nvs_handle;
};

#endif