#include <REGX52.H>
#include "LCD1602.h"
#include "delay.h"
#include "timer0.h"

// to show clock:00:00:00

unsigned int second = 0;
unsigned int minute = 0;
unsigned int hour = 0;
void main() {
  LCD_Init();
  timer0_init();
  LCD_ShowString(1, 1, "Clock:");
  while (1) {
    if (hour < 10) {
      LCD_ShowNum(1, 7, 0, 1);
      LCD_ShowNum(1, 8, hour, 1);
    } else {
      LCD_ShowNum(1, 7, hour, 2);
    }
    LCD_ShowChar(1, 9, ':');
    if (minute < 10) {
      LCD_ShowNum(1, 10, 0, 1);
      LCD_ShowNum(1, 11, minute, 1);
    } else {
      LCD_ShowNum(1, 10, minute, 2);
    }
    LCD_ShowChar(1, 12, ':');
    if (second < 10) {
      LCD_ShowNum(1, 13, 0, 1);
      LCD_ShowNum(1, 14, second, 1);
    } else {
      LCD_ShowNum(1, 13, second, 2);
    }
  }
}

void timer0_routine() interrupt 1 {
  static unsigned int timer0_count = 0;
  TH0 = 64535 / 256;
  TL0 = 64535 % 256;
  timer0_count++;
  // each 1ms do the following instruction
  if (timer0_count >= 300) {
    timer0_count = 0;
    second++;
    if (second == 60) {
      second = 0;
      minute++;
      if (minute == 60) {
        minute = 0;
        hour++;
      }
    }
  }
}
