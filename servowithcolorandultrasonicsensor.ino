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
const int trigPin = 2;
const int echoPin = 3;
unsigned long ultrasonicStartTime = 0;
unsigned long colorSensorStartTime = 0;
const unsigned long programDuration = 120000; // 2 minutes for the whole program

void setup() {
  Serial.begin(9600);

  // Attach servos to pins
  servoUltrasonic.attach(6); // Adjust pin as needed for the first servo controlled by ultrasonic sensor
  servoRed.attach(9);
  servoGreen.attach(10);
  servoBlue.attach(11);

  // Ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Perform calibration at startup
  calibrateSensor();
}

void loop() {
  // Measure distance with ultrasonic sensor
  float distance = measureDistance();

  // Check if ultrasonic sensor detected the required distance
  if (distance < 10 && millis() - ultrasonicStartTime < programDuration) {
    // Ultrasonic sensor detected the required distance, and the program duration is not exceeded
    // Move the first servo controlled by ultrasonic sensor to a specific position
    if (servoUltrasonic.read() != 90) {
      servoUltrasonic.write(90); // Adjust the position as needed
      delay(500); // Adjust the delay as needed
    }

    // Start color sensor and servo control
    detectColorAndControlServos();
  } else {
    // Ultrasonic sensor did not detect the required distance or the program duration is exceeded
    // Stop all servos and wait for the program to finish
    stopAllServos();
  }

  delay(100);
}

void calibrateSensor() {
  // Calibration function (same as before)
  calibR = 1.2;  // Adjust as needed
  calibG = 1.0;  // Adjust as needed
  calibB = 0.8;  // Adjust as needed
}

void detectColorAndControlServos() {
  uint16_t r, g, b, c;

  tcs.getRawData(&r, &g, &b, &c);

  // Apply calibration to raw values
  r *= calibR;
  g *= calibG;
  b *= calibB;

  // Normalize the values to the 0-255 range
  r = constrain(r, 0, 255);
  g = constrain(g, 0, 255);
  b = constrain(b, 0, 255);

  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");

  // Control servos based on color
  if (r > g && r > b) {
    // Red detected
    stopServo(servoGreen);
    stopServo(servoBlue);
    servoRed.write(90); // Move the red servo to a specific position
  } else if (g > r && g > b) {
    // Green detected
    stopServo(servoRed);
    stopServo(servoBlue);
    servoGreen.write(90); // Move the green servo to a specific position
  } else if (b > r && b > g) {
    // Blue detected
    stopServo(servoRed);
    stopServo(servoGreen);
    servoBlue.write(90); // Move the blue servo to a specific position
  } else {
    // No dominant color detected, stop all color servos
    stopAllColorServos();
  }

  // Keep the
