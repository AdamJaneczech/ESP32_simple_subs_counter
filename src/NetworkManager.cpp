#include <NetworkManager.hpp>

NetworkManager::NetworkManager(){
    
}

void NetworkManager::beginWiFi(const char* ssid, const char* password, uint8_t timeout_s){
    WiFi.begin(ssid, password);
    networkTimeout = timeout_s;
}

void NetworkManager::sendConfigPage(){
    server.send(100, "text/html", ConfigPage);
}

void NetworkManager::beginServer(char* ssid, char* password){
    WiFi.disconnect();
    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(local, gateway, subnet);

    server.on("/", sendConfigPage);
    server.begin();
}

uint8_t NetworkManager::wifiStatus(){
    bool status = false;
    if(WiFi.status() == WL_CONNECTED){
        status = true;
    }
    return status;
}