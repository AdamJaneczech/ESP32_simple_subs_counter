#include <icons.hpp>
/*
needs to be defined by user, ignored by git
*/
#include <secrets.hpp>

#include <Adafruit_SSD1306.h>
#include <Adafruit_BusIO_Register.h>

#include <Raleway_SemiBold6pt7b.hpp>
#include <Raleway_SemiBold8pt7b.hpp>
#include <Raleway_SemiBold10pt7b.hpp>
#include <Raleway_SemiBold12pt7b.hpp>
#include <Raleway_SemiBold18pt7b.hpp>
#include <Raleway_SemiBold21pt7b.hpp>

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

        void setSizePt(uint8_t size);

        void setPosition(uint8_t x, uint8_t y);

    private:
        uint8_t sizePt;
};