#include <Arduino.h>
#include <FastLED.h>
#include "CtrlCenter.h"

#define LED_PIN     18        // 你接 DIN 的 GPIO
#define NUM_LEDS    18        // 灯珠数量
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

uint8_t brightness = 0;
int8_t step = 3;
CtrlCenter& m_CtrlCenter = CtrlCenter::Instance();

void setup() {
  m_CtrlCenter.Init();
}

void loop() {
  m_CtrlCenter.Update();
  
}
