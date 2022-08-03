#include <NetworkManager.hpp>

NetworkManager::NetworkManager(){
    
}

void NetworkManager::beginWiFi(const char* ssid, const char* password, uint8_t timeout_s){
    //WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    networkTimeout = timeout_s;
}

void NetworkManager::sendConfigPage(){
    
}

void NetworkManager::initAP(const char* ssid, const char* password){
    WiFi.softAP(ssid, password);
    Serial.println(WiFi.softAPIP());
}

uint8_t NetworkManager::wifiStatus(){
    bool status = false;
    if(WiFi.status() == WL_CONNECTED){
        status = true;
    }
    return status;
}