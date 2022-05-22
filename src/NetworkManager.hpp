#include <RalewayDisplay.hpp>

//#include <WiFi.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WebServer.h>

#define CONNECTION_TIMEOUT_BIT 0
#define CONNECTION_TIMEOUT_S 10 

static IPAddress local(192, 168, 0, 1);
static IPAddress gateway(192, 168, 0, 1);
static IPAddress subnet(255,255,255,0);

static WebServer server(80);

static WiFiClient client;
static HTTPClient http;

static RalewayDisplay screen;

#include <ConfigPage.hpp>

class NetworkManager{
    public:
        static void beginWiFi(const char* ssid, const char* password, uint8_t timeout_s);
        static uint8_t wifiStatus();
        static void beginServer(char* ssid, char* password);
        static void sendConfigPage();
    private:
};
