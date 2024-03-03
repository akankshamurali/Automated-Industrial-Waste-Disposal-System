#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h>

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
float calibR = 1.0;
float calibG = 1.0;
float calibB = 1.0;
Servo servoR;
Servo servoG;
Servo servoB;
Servo servoD;
Servo myServo;

void setup() {
  Serial.begin(9600);
  servoR.attach(9);    // Attach the servo to pin 9
  servoG.attach(10); // Attach the servo to pin 10
  servoB.attach(11);
  servoD.attach(6);  // Attach the servo to pin 11
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


    if (r > g && r > b && r > 100) {
     moveServo(servoD, 90);
     Serial.println("R");    
     moveServo(servoR, 0); 
    } else if (g > r && g > b && g > 100) {
      moveServo(servoD, 90);
      Serial.println("G");
      moveServo(servoG, 0); 
    } else if (b > r && b > g && b > 100) {
      moveServo(servoD, 90);
      Serial.println("B");
      moveServo(servoB, 0); 
    }

  delay(1000);

  stopServos();
}

void calibrateSensor() {
  calibR = 1.2;  
  calibG = 1.8;  
  calibB = 2.2; 
}

void moveServo(Servo &servo, int angle) {
  servo.write(angle);
  //delay(5000);  
  }
void stopServos() {
  servoR.write(48); //need to cali
  servoG.write(48);
  servoB.write(48);
  servoD.write(0);
}
