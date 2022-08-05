#include <RalewayDisplay.hpp>

#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WebServer.h>

static IPAddress local(192, 168, 0, 1);
static IPAddress gateway(192, 168, 0, 1);
static IPAddress subnet(255,255,255,0);

static WiFiServer server(80);

static HTTPClient http;

static RalewayDisplay screen;

static String header;

static const char* input_1 = "ssid";
static const char* input_2 = "password";

static const char* SSID_path = "/ssid.cfg";
static const char* password_path = "/password.cfg";

#include <Config.hpp>

class NetworkManager{
    public:
        NetworkManager();
        static bool beginWiFi(const char* ssid, const char* password);
        static uint8_t wifiStatus();
        static void initAP(const char* ssid, const char* password);
        static void sendConfigPage();
    private:
};
