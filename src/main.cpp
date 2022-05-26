#include <NetworkManager.hpp>
/*
needs to be defined by user, ignored by git - define your SSID, PASSWORD & the Google API link
*/
#include <secrets.hpp>

NetworkManager networkManager;

uint8_t state = 0;

void setup() {
  Serial.begin(115200);
  //Wire.setClock(1000000);
  networkTimerInit();
  setNetworkTimer_s(DEFAULT_NETWORK_TIMEOUT);

  screen.init();
  screen.loadingScreen();

  networkManager.beginWiFi(SSID, PASSWORD, 10);

  while (!(global & 1 << CONNECTION_TIMEOUT_BIT) && WiFi.status() != WL_CONNECTED)
  {
    ;
  }
  //contrast test
  /*for(uint8_t contrast = 0; contrast < 255; contrast++){
    Wire.beginTransmission(DISPLAY_ADDRESS);
    Wire.write(0x00);
    Wire.write(SSD1306_SETCONTRAST);
    Wire.endTransmission();
    Wire.beginTransmission(DISPLAY_ADDRESS);
    Wire.write(0x00);
    Wire.write(contrast);
    Wire.endTransmission();
    delay(10);
  }*/
  if(!(global & 1 << CONNECTION_TIMEOUT_BIT)){
    Serial.println("timeout");
    //screen.showServerQR();
  }
  Serial.println("there");
  screen.display->clearDisplay();
  screen.homeScreen();
}

void loop() {
  http.begin(API_LINK);
  if(http.GET() > 0){
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

    const char* items_0_statistics_viewCount = items_0_statistics["viewCount"];
    const char* items_0_statistics_subscriberCount = items_0_statistics["subscriberCount"]; 
    const char* items_0_statistics_videoCount = items_0_statistics["videoCount"];

    screen.clearDisplayArea();
    switch(state){
      case 0:
        screen.displayViews(items_0_statistics_viewCount);
        break;
      case 1:
        screen.displaySubs(items_0_statistics_subscriberCount);
        break;
      case 2:
        screen.displayVideoCount(items_0_statistics_videoCount);
        break;
    }
    state++;
    if(state > 2){
      state = 0;
    }
    delay(5000);
  }
  http.end();
}