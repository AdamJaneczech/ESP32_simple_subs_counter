#include <NetworkManager.hpp>

NetworkManager::NetworkManager(){
    
}

bool NetworkManager::beginWiFi(const char* ssid, const char* password){  
    if(strlen(ssid) == 0 || strlen(password) < 8){
        return false;
    }
    else{
        WiFi.begin(ssid, password);
        return true;
    }
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