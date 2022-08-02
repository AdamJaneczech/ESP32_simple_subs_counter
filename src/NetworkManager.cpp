#include <NetworkManager.hpp>

NetworkManager::NetworkManager(){
    
}

void NetworkManager::beginWiFi(const char* ssid, const char* password, uint8_t timeout_s){
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    networkTimeout = timeout_s;
}

void NetworkManager::sendConfigPage(){
    
}

void NetworkManager::beginServer(const char* ssid, const char* password){
    //WiFi.disconnect();
    //WiFi.mode(WIFI_MODE_AP);
    //WiFi.softAPConfig(local, gateway, subnet);
    WiFi.softAP(ssid, password);
    Serial.println(WiFi.softAPIP());
    //Serial.println(WiFi.localIP());
    server.begin();
}

uint8_t NetworkManager::wifiStatus(){
    bool status = false;
    if(WiFi.status() == WL_CONNECTED){
        status = true;
    }
    return status;
}