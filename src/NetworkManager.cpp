#include <NetworkManager.hpp>

void NetworkManager::beginWiFi(char* ssid, char* password, uint8_t timeout_s){
    WiFi.begin(ssid, password);
    screen.loadingScreen(uint16_t(0));
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