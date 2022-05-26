#include <NetworkManager.hpp>
/*
needs to be defined by user, ignored by git - define your SSID, PASSWORD & the Google API link
*/
#include <secrets.hpp>

NetworkManager networkManager;

hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

uint8_t state = 0;
uint8_t global = 0;

static void IRAM_ATTR connectionISR(){
  global ^= 1 << CONNECTION_TIMEOUT_BIT;
  //Serial.println("interrupt");
}

void setup() {
  Serial.begin(115200);
  //Wire.setClock(1000000);
  screen.init();

  screen.loadingScreen(1);
  networkManager.beginWiFi(SSID, PASSWORD, 10);

  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &connectionISR, true);
  timerAlarmWrite(timer, 1e6 * 10, true);
  timerAlarmEnable(timer);
  while (!(global & 1 << CONNECTION_TIMEOUT_BIT))
  {
    ;
  }
  if(!(global & 1 << CONNECTION_TIMEOUT_BIT)){
    Serial.println("timeout");
    //screen.showServerQR();
  }
  /*screen.display->clearDisplay();
  screen.homeScreen();*/
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