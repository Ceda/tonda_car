#include <Arduino.h>

// #include "buttons.h"
#include "display.h"

// Display port
unsigned int ST_CP = 10; // RCLK
unsigned int SH_CP = 9;  // SCLK
unsigned int DS    = 8;  // DIO

// Rotary Encoder
unsigned int ENCODER_PIN_A = 2;
unsigned int ENCODER_PIN_B = 3;

Display display(ST_CP, SH_CP, DS, ENCODER_PIN_A, ENCODER_PIN_B);


void setup() {
  display.setup();

}

void loop() {
  display.loop();
}
