#include <NetworkManager.hpp>

#define CONNECTION_TIMEOUT_BIT 0
#define CONNECTION_TIMEOUT_S 10 

hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

uint8_t state = 0;
uint8_t global = 0;