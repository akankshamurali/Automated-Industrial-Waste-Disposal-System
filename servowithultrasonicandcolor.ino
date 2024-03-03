#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h>

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
float calibR = 1.0;
float calibG = 1.0;
float calibB = 1.0;
Servo servoU;
Servo servoR;
Servo servoG;
Servo servoB;
Servo myservo;

const int pingPin = 7; 
unsigned long ultrasonicStartTime = 0;
unsigned long colorSensorStartTime = 0;
const unsigned long programDuration = 100; 
void setup() {
  Serial.begin(9600);

  servoU.attach(6); 
  servoR.attach(9);
  servoG.attach(10);
  servoB.attach(11);
  pinMode(pingPin, OUTPUT);
  calibrateSensor();
}

void loop() {
  float distance = measureDistance();
  Serial.print("dist: "); 
  Serial.println(" ");
  if (distance < 10 && millis() - ultrasonicStartTime < programDuration) {
    if (servoU.read() != 90) {
      servoU.write(90); 

      delay(500); 
    }
    detectColor();
  } else {
    stopAllServos();
  }

  delay(100);
}


void calibrateSensor() {
  calibR = 1.2;  
  calibG = 1.8; 
  calibB = 2.2;  
}

void detectColor() {
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

  if (r > g && r > b) {
    // Red detected
    stopServo(servoG);
    stopServo(servoB);
    servoR.write(90); 
  } else if (g > r && g > b) {
    // Green detected
    stopServo(servoR);
    stopServo(servoB);
    servoG.write(90); 
  } else if (b > r && b > g) {
    // Blue detected
    stopServo(servoR);
    stopServo(servoG);
    servoB.write(90); 
  } else {
    stopAllServos();
  }
  delay(programDuration - (millis() - colorSensorStartTime));
}

void stopAllServos() {
  stopServo(servoU);
  stopServo(servoR);
  stopServo(servoG);
  stopServo(servoB);
}

void stopServo(Servo myservo) {
  myservo.write(0);
}

float measureDistance() {
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  //return pulseIn(pingPin, HIGH) * 0.034 / 2;
}
