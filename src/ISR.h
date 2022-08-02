#define CONNECTION_TIMEOUT_BIT 0
#define SCROLL_TIMEOUT_BIT 1
#define DEFAULT_NETWORK_TIMEOUT 10
#define DEFAULT_SCROLL_TIMEOUT 5

#include <Arduino.h>

static hw_timer_t * timer = NULL;
static portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

static uint8_t global = 0;
static uint8_t networkTimeout;

static void IRAM_ATTR connectionISR(){
  global |= 1 << CONNECTION_TIMEOUT_BIT;
  Serial.println(global, BIN);
}

static void IRAM_ATTR scrollISR(){
  global |= 1 << SCROLL_TIMEOUT_BIT;
}

static void networkTimerInit(){
  //set the prescaler to 80 - the chip frequency is 80 MHz
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &connectionISR, true);
}

static void setNetworkTimer_s(uint8_t secs){
  networkTimeout = secs;
  timerAlarmWrite(timer, 1e6 * networkTimeout, true);
  timerAlarmEnable(timer);
}

static void scrollTimerInit(){
  global |= 1 << SCROLL_TIMEOUT_BIT;
  timerAttachInterrupt(timer, &scrollISR, true);
}

static void setScrollTimer_s(uint8_t secs){
  timerAlarmWrite(timer, 1e6 * secs, true);
  timerAlarmEnable(timer);
}