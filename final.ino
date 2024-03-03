#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h>

// Pin configuration
const int pingPin = 7; 
const int servoUPin = 5; 
const int servoDPin = 6;     
const int servo1Pin = 9;    
const int servo2Pin = 10;   
const int servo3Pin = 11;  
Servo servoU;
Servo servoD;
Servo servo1;             
Servo servo2;               
Servo servo3;               


Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);
  servo1.attach(servo1Pin);  
  servo2.attach(servo2Pin);  
  servo3.attach(servo3Pin); 
  servoU.attach(servoUPin);
  servoD.attach(servoDPin); 
}
uint16_t r, g, b, c;
unsigned long initMillis;
unsigned long currentMillis;
unsigned long interval = 2000;
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
  delay(1000);

  if (distance < 10) {

    moveServo(servoU, 90);
    delay(5000);

    initMillis = millis();
    currentMillis = millis();
    while(currentMillis - initMillis < interval){
      currentMillis = millis();
      tcs.getRawData(&r, &g, &b, &c);
    

    Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
    Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
    Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
    Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
    Serial.println(" ");

    if (r > g && r > b && r > 20) {
      moveServo(servoD, 110); 
      Serial.println("R");  
      moveServo(servo1, 0); 
    } else if (g > r && g > b && g > 20) {
      moveServo(servoD, 110);
      Serial.println("G");   
      moveServo(servo2, 0); 
    } else if (b > r && b > g && b > 20) {
      moveServo(servoD, 110); 
      Serial.println("B");  
      moveServo(servo3, 0); 
    }
    }
    // delay(2000);  
  }
  stopServo();

  // delay(1000);  
}
void moveServo(Servo &servo, int angle) {
  servo.write(angle);
  //delay(5000);  
  }
void stopServo() {
  servo1.write(50); //need to cali
  servo2.write(50);
  servo3.write(50);
  servoD.write(180);
  servoU.write(165);
  //delay(5000);  
  }
 

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
