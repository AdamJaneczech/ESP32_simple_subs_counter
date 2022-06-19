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

void RalewayDisplay::loadingScreen(){
    display->drawBitmap(30, 8, wifi_48px, 69, 48, WHITE);
    display->display();
}

void RalewayDisplay::homeScreen(){
    display->drawBitmap(0, 0, fluni, DISPLAY_WIDTH, 29, WHITE);
    display->display();
}

void RalewayDisplay::setPosition(uint8_t x, uint8_t y){
    display->setCursor(x, y + (uint8_t)sizePt + 1);
}

void RalewayDisplay::clearDisplayArea(){
    display->fillRect(0,29,DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1, BLACK);
    display->display();
}

void RalewayDisplay::displayViews(const char* views){
    clearDisplayArea();
    if(strlen(views) <= 6){
        setSizePt(SIZE_LARGE_12pt);
        setPosition(0, 46);
    }
    else if(strlen(views) > 6){
        setSizePt(SIZE_LARGE_12pt);
        setPosition(0, 48);
    }
    display->print(views);
    setSizePt(SIZE_SMALL_8pt);
    display->print(" views");
    display->display();
}

void RalewayDisplay::displaySubs(const char* subs){
    clearDisplayArea();
    if(strlen(subs) <= 6){
        setSizePt(SIZE_LARGE_12pt);
        setPosition(0, 46);
    }
    else if(strlen(subs) > 6){
        setSizePt(SIZE_LARGE_12pt);
        setPosition(0, 48);
    }
    display->print(subs);
    setSizePt(SIZE_SMALL_6pt);
    display->print(" subscribers");
    display->display();
}

void RalewayDisplay::displayVideoCount(const char* videos){
    clearDisplayArea();
    if(strlen(videos) <= 2){
        setSizePt(SIZE_LARGE_18pt);
        setPosition(0, 37);
    }
    else if(strlen(videos) > 2){
        setSizePt(SIZE_LARGE_12pt);
        setPosition(0, 46);
    }
    display->print(videos);
    setSizePt(SIZE_MID_10pt);
    display->print(" videos");
    display->display();
}

void RalewayDisplay::animateLeft(uint8_t stateNum, char* num){
    switch(stateNum){
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
    }
}

void RalewayDisplay::showServerQR(){
    display->clearDisplay();
    Wire.beginTransmission(DISPLAY_ADDRESS);
    Wire.write(0x00);
    Wire.write(SSD1306_SETCONTRAST);
    Wire.endTransmission();
    Wire.beginTransmission(DISPLAY_ADDRESS);
    Wire.write(0x00);
    Wire.write(1);
    Wire.endTransmission();
    display->drawBitmap(0, 0, WiFiQR, 64, 64, WHITE);
    display->display();
}