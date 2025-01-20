#include "nvs_manager.h"

NVSManager::NVSManager() {
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        nvs_flash_init();
    }
}

bool NVSManager::saveData(const char* key, const char* value) {
    esp_err_t err = nvs_open("storage", NVS_READWRITE, &nvs_handle);
    if (err != ESP_OK) return false;
    err = nvs_set_str(nvs_handle, key, value);
    if (err != ESP_OK) return false;
    err = nvs_commit(nvs_handle);
    nvs_close(nvs_handle);
    return err == ESP_OK;
}

String NVSManager::readData(const char* key) {
    static char value[256];
    size_t len = sizeof(value);
    esp_err_t err = nvs_open("storage", NVS_READONLY, &nvs_handle);
    if (err != ESP_OK) return "";
    err = nvs_get_str(nvs_handle, key, value, &len);
    nvs_close(nvs_handle);
    return (err == ESP_OK) ? String(value) : "";
}