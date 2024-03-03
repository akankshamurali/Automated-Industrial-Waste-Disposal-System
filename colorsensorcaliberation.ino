#include <Wire.h>
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
float calibR = 1.0;
float calibG = 1.0;
float calibB = 1.0;

void setup() {
  Serial.begin(9600);
  calibrateSensor();
}

void loop() {
  uint16_t r, g, b, c;

  tcs.getRawData(&r, &g, &b, &c);
  r *= calibR;
  g *= calibG;
  b *= calibB;
  r = constrain(r, 0, 255);
  g = constrain(g, 0, 255);
  b = constrain(b, 0, 255);

  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");

  delay(2000);
}

void calibrateSensor() {
  calibR = 1.2;  
  calibG = 1.8;  
  calibB = 2.2;  
}
