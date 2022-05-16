#include <Arduino.h>

#include <Adafruit_SSD1306.h>
#include <Adafruit_BusIO_Register.h>

#include <Raleway_SemiBold6pt7b.hpp>
#include <Raleway_SemiBold8pt7b.hpp>
#include <Raleway_SemiBold12pt7b.hpp>

#define SIZE_6pt 

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DISPLAY_RESET -1
#define DISPLAY_ADDRESS 0x3C

class RalewayDisplay{
    public:
        RalewayDisplay();

        Adafruit_SSD1306* display;

        void init();

        void setPosition(uint8_t x, uint8_t y);

        void setSize(uint8_t size);
    private:

};