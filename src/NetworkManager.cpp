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
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Connecting...");
        return;
    }
    Serial.println();
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

uint8_t NetworkManager::wifiStatus(){
    bool status = false;
    if(WiFi.status() == WL_CONNECTED){
        status = true;
    }
    return status;
}