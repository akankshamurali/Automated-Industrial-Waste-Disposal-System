#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h>

const int pingPin = 7;      
const int servoPin = 9;     

Servo myServo;               
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);  
  if (tcs.begin()) {
    Serial.println("Color sensor initialized");
  } else {
    Serial.println("Error initializing color sensor");
    while (1);
  }
}

void loop() {

  long duration, distance;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  distance = microsecondsToCentimeters(duration);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 10) {
    // Move the servo
    myServo.write(90);  
    delay(2000);  
     

    uint16_t r, g, b, c;
    tcs.getRawData(&r, &g, &b, &c);

    Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
    Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
    Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
    Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
    Serial.println(" ");
    delay(5000);

    myServo.write(0); 

  }

  delay(100);  
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
