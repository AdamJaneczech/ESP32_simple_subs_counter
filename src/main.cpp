#include <Arduino.h>

#include <Adafruit_SSD1306.h>
#include <Adafruit_BusIO_Register.h>

#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
//needs to be defined by user, ignored by git
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
  Wire.setClock(1000000);
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
  uint32_t time = millis();
  byte width;
  while (WiFi.status() != WL_CONNECTED)
  {
    while(WiFi.status() != WL_CONNECTED){
      if(repeats < 32){
        width = repeats;
        display.fillRect(0, 61, width, 2, WHITE);
        display.display();
        display.fillRect(repeats-1, 61, width, 2, BLACK);
      }
      else if(repeats > 128){
        width = 160-repeats;
      }
      if(repeats > 32 && repeats < 160){
        display.fillRect(0, 61, 128, 2, BLACK);
        display.fillRect(repeats - 32, 61, width, 2, WHITE);
        display.display();
      }
      time = millis();
      if(repeats == 160){
        repeats = 0;
        width = 0;
        display.fillRect(0, 61, 128, 2, BLACK);
        display.display();
      }
      else{
        repeats++;
      }
    }
    display.clearDisplay();
  }
}

void loop() {
  http.begin(API_LINK);
  if(http.GET() > 0){
    display.clearDisplay();

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