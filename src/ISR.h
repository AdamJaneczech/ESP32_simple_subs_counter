#define CONNECTION_TIMEOUT_BIT 0
#define DEFAULT_NETWORK_TIMEOUT 10

#include <Arduino.h>

static hw_timer_t * timer = NULL;
static portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

static uint8_t global = 0;
static uint8_t networkTimeout;

static void IRAM_ATTR connectionISR(){
  global ^= 1 << CONNECTION_TIMEOUT_BIT;
  Serial.println(global, BIN);
}

static void networkTimerInit(){
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &connectionISR, true);
}

static void setNetworkTimer_s(uint8_t secs){
    networkTimeout = secs;
    timerAlarmWrite(timer, 1e6 * networkTimeout, true);
    timerAlarmEnable(timer);
}