#include <RalewayDisplay.hpp>

RalewayDisplay::RalewayDisplay(){
    display = new Adafruit_SSD1306(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, -1);
}

void RalewayDisplay::setSizePt(uint8_t fontPt){
    sizePt = fontPt;
    switch(fontPt){
        default:
            display->setFont(&Raleway_SemiBold6pt7b);
            break;
        case 6:
            display->setFont(&Raleway_SemiBold6pt7b);
            break;
        case 8:
            display->setFont(&Raleway_SemiBold8pt7b);
            break;
        case 10:
            display->setFont(&Raleway_SemiBold10pt7b);
            break;
        case 12:
            display->setFont(&Raleway_SemiBold12pt7b);
            break;
        case 18:
            display->setFont(&Raleway_SemiBold18pt7b);
            break;
        case 21:
            display->setFont(&Raleway_SemiBold21pt7b);
            break;
    }
}

void RalewayDisplay::init(){
    display->begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS);
    display->clearDisplay();
    display->setTextColor(WHITE);
}

void RalewayDisplay::loadingScreen(char* ssid){
    setSizePt(SIZE_SMALL_6pt);
    setPosition(0,0);
    display->print("SSID: ");
    display->print(ssid);
}

void RalewayDisplay::loadingScreen(uint16_t timeout){
    display->drawBitmap(30, 8, wifi_48px, 69, 48, WHITE);
    display->display();
}

void RalewayDisplay::setPosition(uint8_t x, uint8_t y){
    display->setCursor(x, y + (uint8_t)sizePt + 1);
}