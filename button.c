#include "button.h"

#include <REGX52.H>

#include "delay.h"
#include "port_name.h"


unsigned char button_press() {
  unsigned char button_value = 0;
  if (BUTTON1 == BUTTON_ON) {
    delay(20);
    while (BUTTON1 == BUTTON_ON) {
      delay(20);
      button_value = 1;
    }
  }
  if (BUTTON2 == BUTTON_ON) {
    delay(20);
    while (BUTTON2 == BUTTON_ON) {
      delay(20);
      button_value = 2;
    }
  }
  if (BUTTON3 == BUTTON_ON) {
    delay(20);
    while (BUTTON3 == BUTTON_ON) {
      delay(20);
      button_value = 3;
    }
  }
  if (BUTTON4 == BUTTON_ON) {
    delay(20);
    while (BUTTON4 == BUTTON_ON) {
      delay(20);
      button_value = 4;
    }
  }
  return button_value;
}
