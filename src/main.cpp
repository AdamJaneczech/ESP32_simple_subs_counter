#include <FLUNI_ticker.hpp>
/*
needs to be defined by user, ignored by git - define your SSID, PASSWORD & the Google API link
*/
#include <secrets.hpp>

NetworkManager networkManager;

uint8_t state = 0;

void setup() {
  Serial.begin(115200);

  networkTimerInit();
  setNetworkTimer_s(DEFAULT_NETWORK_TIMEOUT);

  screen.init();
  screen.loadingScreen();

  if (!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  Serial.println("SPIFFS mounted successfully");
  writeFile(SPIFFS, SSID_path, "abcd");
  SSID = readFile(SPIFFS, SSID_path);
  //PASSWORD = readFile(SPIFFS, password_path);

  Serial.println(SSID);
  Serial.println("below");
  Serial.println(strlen(SSID));
  Serial.println(PASSWORD);

  networkManager.beginWiFi(SSID, PASSWORD);

  Serial.println("below");

  while(!(global & 1 << NO_CONNECTION_BIT) && WiFi.status() != WL_CONNECTED){

  }

  if(global & 1 << NO_CONNECTION_BIT){
    networkManager.initAP(ESP_SSID, ESP_PASSWORD);

    screen.showServerQR();
    screen.showServerCredentials(ESP_SSID, ESP_PASSWORD);

    server.begin();

    // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    //   request->send_P(200, "text/html", ConfigPage, (const char*)' ');
    // });
    
    /* while(!(global & 1 << SERVER_SUBMIT_BIT)){
      WiFiClient client = server.available();
      
      if(client){
        Serial.println("New client");
        String currentLine = "";
        global &= ~(1 << NO_CONNECTION_BIT);

        while(client.connected()){
          if(client.available()){
            char c = client.read();
            Serial.write(char(c));
            header += c;
            
            if(c == '\n'){
              if(currentLine.length() == 0){
                Serial.println(header);
                client.println("HTTP/1.1 200 OK");
                client.println("Content-type:text/html");
                client.println("Connection: close");
                client.println();
                client.print(ConfigPage);
                client.println();
                break;
              }
              else{
                currentLine = "";
              }
            }

            else if (c != '\r') {  // if you got anything else but a carriage return character,
              currentLine += c;      // add it to the end of the currentLine
            }
          }
        }
        client.stop();
        header = "";
        Serial.println("Client disconnected");
      }
    } */
  }
  
  timerDetachInterrupt(timer);

  scrollTimerInit();
  setScrollTimer_s(DEFAULT_SCROLL_TIMEOUT);

  screen.display->clearDisplay();
  screen.homeScreen();
}

void loop() {
  http.begin(API_LINK);
  if(http.GET() > 0 && global & 1 << SCROLL_TIMEOUT_BIT){
    
    global &= ~(1 << SCROLL_TIMEOUT_BIT);
    
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
  }
  http.end();
}