#include <RalewayDisplay.hpp>
#include <secrets.hpp>
/*
needs to be defined by user, ignored by git
*/

#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>

WiFiClient client;
HTTPClient http;
RalewayDisplay screen;

uint8_t repeats = 0;


void setup() {
  Serial.begin(115200);
  Wire.setClock(1000000);

  screen.init();
  
  WiFi.begin(SSID, PASSWORD);
  uint32_t time = millis();
  byte width;
  screen.loadingScreen(1);
  while (WiFi.status() != WL_CONNECTED)
  {
    
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

    screen.display->drawBitmap(0, 0, fluni, 128, 29, WHITE);
    screen.setSizePt(12);
    screen.setPosition(0,46);
    screen.display->setTextColor(WHITE);
    screen.display->print(items_0_statistics_viewCount);
    screen.setSizePt(8);
    screen.display->print(" views");
    screen.display->display();
    /*screen.setLine(2);
    screen.display->setTextColor(WHITE);
    screen.display->print(items_0_statistics_subscriberCount);*/
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