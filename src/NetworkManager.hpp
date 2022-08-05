#include <RalewayDisplay.hpp>


//#include <WiFi.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

/* static IPAddress local(192, 168, 0, 1);
static IPAddress gateway(192, 168, 0, 1);
static IPAddress subnet(255,255,255,0); */

static AsyncWebServer server(80);

static HTTPClient http;

static RalewayDisplay screen;

static String header;

#include <Config.hpp>

class NetworkManager{
    public:
        NetworkManager();
        static void beginWiFi(const char* ssid, const char* password, uint8_t timeout_s);
        static uint8_t wifiStatus();
        static void initAP(const char* ssid, const char* password);
        static void sendConfigPage();
    private:
};
