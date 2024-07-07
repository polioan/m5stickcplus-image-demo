#include <M5StickCPlus.h>
#include "cat.h"
#include "error.h"
#include "bsod.h"

#define SCREEN_W 135
#define SCREEN_H 240

volatile uint8_t stage = 0;
volatile bool shouldUpdate = true;
volatile uint8_t y = SCREEN_H;

void setup() {
  M5.begin();
  M5.Lcd.setSwapBytes(true);

  M5.Beep.beep();
}

void loop() {
  M5.update();

  if (shouldUpdate) {
    switch (stage) {
      case 1:
        {
          M5.Lcd.fillScreen(BLACK);
          M5.Lcd.setRotation(0);
          M5.Lcd.pushImage(0, y, SCREEN_W, SCREEN_H, cat);
          y--;
          if (y == 0) {
            stage = 2;
          }
          break;
        }
      case 2:
        {
          M5.Lcd.fillScreen(BLACK);
          M5.Lcd.setRotation(0);
          M5.Lcd.pushImage(0, 0, SCREEN_W, SCREEN_H, error);
          delay(1500);
          M5.Lcd.fillScreen(BLACK);
          M5.Lcd.setRotation(0);
          M5.Lcd.pushImage(0, 0, SCREEN_W, SCREEN_H, bsod);
          shouldUpdate = false;
          break;
        }
      default:
        {
          stage = 0;
          y = SCREEN_H;
          M5.Lcd.fillScreen(WHITE);
          shouldUpdate = false;
        }
    }
  }

  if (M5.BtnA.wasReleased() && !shouldUpdate) {
    stage++;
    shouldUpdate = true;
  }
}