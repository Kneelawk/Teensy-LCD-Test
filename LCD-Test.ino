#include <CoopThreads.h>

CoopThreads<8192> threads(8);

void setup() {
  // setup LCD control pins
  pinMode(30, OUTPUT); // Reg Select
  pinMode(31, OUTPUT); // Enable / Clk

  // setup LCD data pins
  pinMode(19, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(16, OUTPUT);

  // configure LCD
  digitalWriteFast(30, LOW);
  digitalWriteFast(31, LOW);
  threads.delay(40); // wait for LCD to power up
  lcdPut(0x30); // wake up
  threads.delay(5); // wait
  lcdPut(0x30); // Wake Up
  threads.delayMicroseconds(160);
  lcdPut(0x30); // WAKE UP
  threads.delayMicroseconds(160);
  lcdPut(0x38); // set display mode
  lcdPut(0x01); // clear display
  threads.delay(3);
  lcdPut(0x0C); // display on, cursor on
  lcdPut(0x06); // entry mode setup

  // write something
  digitalWrite(30, HIGH);
  lcdPut('H');
  lcdPut('e');
  lcdPut('l');
  lcdPut('l');
  lcdPut('o');
  lcdPut(' ');
  lcdPut('W');
  lcdPut('o');
  lcdPut('r');
  lcdPut('l');
  lcdPut('d');
  lcdPut('!');
}

void loop() {
  // put your main code here, to run repeatedly:
}

// Sends a byte to the LCD
void lcdPut(uint8_t c) {
  digitalWriteReg6Shift(0xFF, c, 16);
  digitalWriteFast(31, HIGH);
  threads.delayNanoseconds(500);
  digitalWriteFast(31, LOW);
  threads.delayMicroseconds(60);
}

// Writes data to the 6th register all at once with the specified bitshift
void digitalWriteReg6Shift(uint32_t mask, uint32_t data, uint32_t shift) {
  digitalWriteReg6(mask << shift, data << shift);
}

// Writes data to the 6th register all at once
void digitalWriteReg6(uint32_t mask, uint32_t data) {
  GPIO6_DR = (data & mask) | (GPIO6_DR & ~mask);
}
