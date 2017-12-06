/* Color Servo Control
 * ----------------------
 *
 * Rotate a 180 degree Servo motor connected to digital pin 10 to the middle
 * when red color sensed, clockwise when blue sense & counterclockwise when 
 * green is sensed.
 * 
 * In my setup, this requires 4 AA batteries to power the Servo & USB connection 
 * to power the Arduino Uno board.
 */

//Servo Control
#include <Servo.h>

//Light sensor control
#include <Wire.h>
#include "Adafruit_TCS34725.h"


// set to false if using a common cathode LED - standard from docs
#define commonAnode true

// our RGB -> eye-recognized gamma color
byte gammatable[256];

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);


//Define our Servo
Servo servoMain;

// set input pins for  pushbuttons
int inPinCounter = 4;        
int inPinClockwise = 3;

//Set vars to 0
int ValinPinCounter = 0;
int ValinPinClockwise = 0;

void setup() {
  Serial.begin(9600);

  //Check if color sensor present
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }

  // declare pushbuttons as inputs
  //pinMode(inPinCounter, INPUT_PULLUP);       
  //pinMode(inPinClockwise, INPUT_PULLUP);
  
  // attach servo on digital pin 10
  servoMain.attach(10);                   

  // Return Servo to center position on initial load
  servoMain.write(90);                   
}

void loop(){
  //ValinPinCounter = digitalRead(inPinCounter);
  //ValinPinClockwise = digitalRead(inPinClockwise);
  
  uint16_t clear, red, green, blue;

  tcs.setInterrupt(false); // turn on LED

  //delay(60);  // takes 50ms to read 
  delay(3000);  // takes 50ms to read 
  
  tcs.getRawData(&red, &green, &blue, &clear);

  tcs.setInterrupt(true);  // turn off LED
  
  if (red > green and red > blue) {
    Serial.print("This item is predominantly red.");
    servoMain.write(90); 
  } else if (green > red and green > blue) {
    Serial.print("This item is predominantly green.");
    servoMain.write(180); 
  } else if (blue > red and blue > red) {
    Serial.print("This item is predominantly blue.");
    servoMain.write(0);
  } else {
    Serial.print("I have no idea what color this is.");
  }
  
  Serial.println(); //New line
  
}
