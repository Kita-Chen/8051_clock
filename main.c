#include <REGX52.H>

#include "LCD1602.h"
#include "button.h"
#include "delay.h"
#include "timer0.h"

// to show clock:00:00:00

unsigned int second = 0;
unsigned int minute = 0;
unsigned int hour = 0;
// determine the clock to count or not
unsigned char is_counting = 0;
// determine the speed of clock (with the speed of 1x, 2x, 3x, 4x)
unsigned int speed = 1;

// set the clock to the initial status
void clock_reset() {
  second = 0;
  minute = 0;
  hour = 0;
}

void main() {
  // detect the button to be pressed or not
  unsigned char press;
  LCD_Init();
  timer0_init();
  LCD_ShowString(1, 1, "Clock:");
  while (1) {
    press = button_press();
    // three modes are available
    // mode1(press button 1): reset the clock
    // mode2(press button 2): stop counting / start counting at previous status
    // mode3(press button 3): speed up the clock (if the speed of clock is 4x, next press will set to 1x)
    if (press == 1) {
      clock_reset();
    } else if (press == 2) {
      is_counting = ~is_counting;
    } else if (press == 3) {
      speed++;
      if (speed > 4) {
        speed = 1;
      }
    }
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
  timer0_count += speed;
  // each 1ms do the following instruction
  if (timer0_count >= 1000) {
    timer0_count = 0;
    if (is_counting) {
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
}
