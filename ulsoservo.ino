#include <Servo.h>

// Pin configuration
const int pingPin = 7;  // Trigger pin for Ping sensor
const int servoPin = 9;  // Pin to which the servo is connected

Servo myServo;  // Servo object

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);  // Attaching the servo to its pin
}

void loop() {
  // Measure distance using Ping sensor
  long duration, distance;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // Convert the time into a distance in centimeters
  distance = microsecondsToCentimeters(duration);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


  if (distance < 10) {
    // Move the servo
    myServo.write(90); 
    delay(1000);  
    myServo.write(0);  
  }

  delay(100);  
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
