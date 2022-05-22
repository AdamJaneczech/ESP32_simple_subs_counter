#include <Arduino.h>

#include <icons.hpp>

#include <Adafruit_SSD1306.h>
#include <Adafruit_BusIO_Register.h>

#include <RalewayFonts.hpp>

#define SIZE_SMALL_6pt 6
#define SIZE_SMALL_8pt 8
#define SIZE_MID_10pt 10
#define SIZE_LARGE_12pt 12
#define SIZE_LARGE_18pt 18
#define SIZE_XLARGE_21pt 21

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DISPLAY_RESET -1
#define DISPLAY_ADDRESS 0x3C

class RalewayDisplay{
    public:
        RalewayDisplay();

        Adafruit_SSD1306* display;

        void init();

        void clearDisplayArea();

        void loadingScreen(char* ssid);
        void loadingScreen(uint16_t timeout);   //the timeout will be used with a timer interrupt later

        void homeScreen();

        void displayViews(const char* views);
        void displaySubs(const char* subs);
        void displayVideoCount(const char* videos);

        void animateLeft(uint8_t stateNum, char* num);

        void setSizePt(uint8_t size);

        void setPosition(uint8_t x, uint8_t y);

        void showServerQR();

    private:
        uint8_t sizePt;
};