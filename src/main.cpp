#include <RalewayDisplay.hpp>

#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
//needs to be defined by user, ignored by git
#include <secrets.hpp>

WiFiClient client;
HTTPClient http;
RalewayDisplay screen;

uint8_t repeats = 0;

void setup() {
  Serial.begin(115200);

  screen.display->begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS);
  Wire.setClock(1000000);
  screen.display->clearDisplay();
  screen.display->setTextColor(WHITE);
  screen.display->setTextSize(1);
  screen.display->print("Connecting");
  screen.display->setCursor(0,24);
  screen.display->setTextSize(1);
  screen.display->print("SSID:");
  screen.display->print(SSID);
  screen.display->display();
  screen.display->setCursor(0, 34);
  
  WiFi.begin(SSID, PASSWORD);
  uint32_t time = millis();
  byte width;
  while (WiFi.status() != WL_CONNECTED)
  {
    while(WiFi.status() != WL_CONNECTED){
      if(repeats < 32){
        width = repeats;
        screen.display->fillRect(0, 61, width, 2, WHITE);
        screen.display->display();
        screen.display->fillRect(repeats-1, 61, width, 2, BLACK);
      }
      else if(repeats > 128){
        width = 160-repeats;
      }
      if(repeats > 32 && repeats < 160){
        screen.display->fillRect(0, 61, 128, 2, BLACK);
        screen.display->fillRect(repeats - 32, 61, width, 2, WHITE);
        screen.display->display();
      }
      time = millis();
      if(repeats == 160){
        repeats = 0;
        width = 0;
        screen.display->fillRect(0, 61, 128, 2, BLACK);
        screen.display->display();
      }
      else{
        repeats++;
      }
    }
    screen.display->clearDisplay();
  }
}

void loop() {
  http.begin(API_LINK);
  if(http.GET() > 0){
    screen.display->clearDisplay();

    String payload = http.getString();  // Save all the data on a string
    DynamicJsonDocument doc(1024);

    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }
    
    JsonObject items_0 = doc["items"][0];
    JsonObject items_0_statistics = items_0["statistics"];
    const char* items_0_statistics_viewCount = items_0_statistics["viewCount"]; // "316"
    const char* items_0_statistics_subscriberCount = items_0_statistics["subscriberCount"]; // "3"
    const char* items_0_statistics_videoCount = items_0_statistics["videoCount"]; // "1"

    screen.display->setCursor(0,8);
    screen.display->setTextColor(WHITE);
    screen.display->print(items_0_statistics_viewCount);
    screen.display->setCursor(0,48);
    screen.display->setTextColor(WHITE);
    screen.display->print(items_0_statistics_subscriberCount);
    screen.display->display();
    delay(5000);
  }
  else if (repeats < DISPLAY_WIDTH){
    screen.display->setCursor(0, 44);
    screen.display->print("Getting API info");
    screen.display->writePixel(repeats, 63, WHITE);
    screen.display->display();
    repeats++;
    delay(20);
  }
  http.end();
  // put your main code here, to run repeatedly:
}