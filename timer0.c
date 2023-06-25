#include <REGX52.H>

void timer0_init() {
  // step1: set the "TMOD" register(cannot be given value singlely).
  // ---------------------------------------------------------------
  // 1. Gate = 0, C/~T = 0, Mode = 01.
  // 2. Gate = 0 : not allow external clk to control the system.
  // 3. C/~T = 0 : set T = 1 to operate at timer mode.
  // 4. Mode = 01: set the system to operate at 16-bit mode.
  // 0001 standard for the mode of 16-bit timer without external clk.
  // ---------------------------------------------------------------
  TMOD = TMOD & 0xF0;  // set the lower 4-bit to 0000 and reserve the
                       // higher 4-bit
  TMOD = TMOD | 0x01;  // set the lower 4-bit to 0001 and reserve the
                       // higher 4-bit

  // step2: set the "TCON" register(can be given value singlely)
  // ---------------------------------------------------------------
  // 1. TF0 is timer0 flag, value 1 of TF generate interrupt.
  // 2. TR0 is timer0 ready, to control the operation of timer0.
  // 3. TH0/TL0 represent the initial value of counter, which is the
  //    number of 0 ~ 65535, but both TH0/TL0 are 8-bit registers,
  //    they can only store 0 ~ 255, thus, they should be set together
  //    to represent the number of 0 ~ 65535.
  // ---------------------------------------------------------------
  TF0 = 0;
  TR0 = 1;
  // initialize the counter to be 64535(it takes 1ms to count from 64535 to
  // 65535)
  TH0 = 64535 / 256;
  TL0 = 64535 % 256;

  // step3: set IE(interrupt enable) and IP(interrupt priority).
  // ---------------------------------------------------------------
  // 1. ET0 is enable timer0, set ET0 = 1 to allow interrupt caused by
  //    timer0 to be read.
  // 2. EA is enable access, set EA = 1 to allow interrupt caused by
  //    any timers to pass through.
  // 3. PT0 is priority of timer0, set PT0 = 0 represent interrupt
  //    caused by timer0 is less important.
  // ---------------------------------------------------------------
  ET0 = 1;
  EA = 1;
  PT0 = 0;
}