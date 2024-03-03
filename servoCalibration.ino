/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo servor;
Servo servog;
Servo servob;
Servo servod;
Servo servou;

int pos = 0;  // variable to store the servo position

void setup() {
  servor.attach(9);  // attaches the servo on pin 9 to the servo object
  servog.attach(10);
  servob.attach(11);
  servod.attach(6);
  servou.attach(5);
}
const int rgbHome = 50;
const int dHome = 180;
const int uHome = 70;
void loop() {
  servor.write(rgbHome-50);
  servog.write(rgbHome-50);
  servob.write(rgbHome-50);
  // servod.write(dHome-70);
  // delay(1000);
  servod.write(dHome);
  // servou.write(uHome+80);
  servou.write(uHome);
}