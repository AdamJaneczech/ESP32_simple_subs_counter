#include <RalewayDisplay.hpp>

RalewayDisplay::RalewayDisplay(){
    display = new Adafruit_SSD1306(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, -1);
}