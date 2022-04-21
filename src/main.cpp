#include <Arduino.h>

#include <Adafruit_SSD1306.h>
#include <Adafruit_BusIO_Register.h>

#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include <secrets.hpp>

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DISPLAY_RESET -1
#define DISPLAY_ADDRESS 0x3C

WiFiClient client;
HTTPClient http;
Adafruit_SSD1306 display(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, DISPLAY_RESET);

uint8_t repeats = 0;

void setup() {
  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.print("Connecting");
  display.setCursor(0,20);
  display.setTextSize(1);
  display.print("SSID:");
  display.print(SSID);
  display.display();
  display.setCursor(0, 30);
  
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    while(repeats < DISPLAY_WIDTH){
      delay(10);
      display.writePixel(repeats, 63, WHITE);
      display.display();
      repeats++;
    }
  }
}

void loop() {
  http.begin(API_LINK);
  if(http.GET() > 0){
    display.clearDisplay();

    String payload = http.getString();  // Save all the data on a string
    StaticJsonDocument<1024> doc;

    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }

    const char* kind = doc["kind"]; // "youtube#channelListResponse"
    const char* etag = doc["etag"]; // "N2qzbHxVRFVDT0oPjiUA-fzljVY"

    int pageInfo_totalResults = doc["pageInfo"]["totalResults"]; // 1
    int pageInfo_resultsPerPage = doc["pageInfo"]["resultsPerPage"]; // 5

    JsonObject items_0 = doc["items"][0];
    const char* items_0_kind = items_0["kind"]; // "youtube#channel"
    const char* items_0_etag = items_0["etag"]; // "iBw7hqWnuqbN96IF1A1grvIh5KE"
    const char* items_0_id = items_0["id"]; // "UCRtyvKwmfxntAArnskJjeWQ"

    JsonObject items_0_statistics = items_0["statistics"];
    const char* items_0_statistics_viewCount = items_0_statistics["viewCount"]; // "316"
    const char* items_0_statistics_subscriberCount = items_0_statistics["subscriberCount"]; // "3"
    bool items_0_statistics_hiddenSubscriberCount = items_0_statistics["hiddenSubscriberCount"]; // false
    const char* items_0_statistics_videoCount = items_0_statistics["videoCount"]; // "1"

    display.setCursor(0,0);
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.print(items_0_statistics_viewCount);
    display.setCursor(0,40);
    display.setTextColor(WHITE);
    display.print(items_0_statistics_subscriberCount);
    display.display();
    delay(5000);
  }
  else if (repeats < DISPLAY_WIDTH){
    display.setCursor(0, 40);
    display.print("Getting API info");
    display.writePixel(repeats, 63, WHITE);
    display.display();
    repeats++;
    delay(20);
  }
  http.end();
  // put your main code here, to run repeatedly:
}