/*
  Arduino Starter Kit example
 Project 11  - Crystal Ball
 
 This sketch is written to accompany Project 11 in the
 Arduino Starter Kit
 Created 13 September 2012
 by Scott Fitzgerald
 
 http://arduino.cc/starterKit
 
 This example code is part of the public domain 
 */
#include <MPR121.h>
#include <Wire.h>
#define LOW_DIFF 0
#define HIGH_DIFF 50
#define filterWeight 0.3f // 0.0f to 1.0f - higher value = more smoothing
float lastProx = 0;
#define ELECTRODE 6 // the electrode to monitor
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
const int switchPin = A0;// set up a constant for the touch sensor
int switchState = 0;// variable to hold the value of the switchPin
int prevSwitchState = 0;// variable to hold previous value of the switchpin
int reply;// a variable to choose which reply from the soul reader

void setup() {  
  lcd.begin(16, 2);  
  pinMode(switchPin,INPUT); // set up the switch pin as an input
    // Print a message to the LCD.
  lcd.print("Reveal :)");
  // set the cursor to column 0, line 1
  // line 1 is the second row, since counting begins with 0
  lcd.setCursor(0, 1);
  // print to the second line
  lcd.print("your soles...");

  Serial.begin(9600);
  //while(!Serial);  
  if(!MPR121.begin(0x5A)){ 
    Serial.println("error setting up MPR121");  
    switch(MPR121.getError()){
      case NO_ERROR:
        Serial.println("no error");
        break;  
      case ADDRESS_UNKNOWN:
        Serial.println("incorrect address");
        break;
      case READBACK_FAIL:
        Serial.println("readback failure");
        break;
      case OVERCURRENT_FLAG:
        Serial.println("overcurrent on REXT pin");
        break;      
      case OUT_OF_RANGE:
        Serial.println("electrode out of range");
        break;
      case NOT_INITED:
        Serial.println("not initialised");
        break;
      default:
        Serial.println("unknown error");
        break;      
    }
    while(1);
  }

  // slow down some of the MPR121 baseline filtering to avoid 
  // filtering out slow hand movements
  MPR121.setRegister(MPR121_NHDF, 0x01); //noise half delta (falling)
  MPR121.setRegister(MPR121_FDLF, 0x3F); //filter delay limit (falling)
}

void loop() {
  // update all of the data from the MPR121
  MPR121.updateAll();

  // read the difference between the measured baseline and the measured continuous data
  int reading = MPR121.getBaselineData(ELECTRODE)-MPR121.getFilteredData(ELECTRODE);

  // print out the reading value for debug
  Serial.println(reading); 

  // constrain the reading between our low and high mapping values
  unsigned int prox = constrain(reading, LOW_DIFF, HIGH_DIFF);
  
  // implement a simple (IIR lowpass) smoothing filter
  lastProx = (filterWeight*lastProx) + ((1-filterWeight)*(float)prox);

  // map the LOW_DIFF..HIGH_DIFF range to 0..255 (8-bit resolution for analogWrite)
  uint8_t thisOutput = (uint8_t)map(lastProx,LOW_DIFF,HIGH_DIFF,0,255);

  // output the mapped value to the LED
  analogWrite(switchPin, thisOutput);
  
  // check the status of the switch
  switchState = digitalRead(switchPin);

  // compare the switchState to its previous state
  if (switchState != prevSwitchState) {
    // if the state has changed from HIGH to LOW
    // you know that the ball has been tilted from 
    // one direction to the other 
    if (switchState == HIGH) {
      // randomly chose a reply
      reply = random(8);
      // clean up the screen before printing a new reply
      lcd.clear();    

      // choose a saying to print based on the value in reply 
      switch(reply){
      case 0:
        delay(1500);
        lcd.print("Your sole says");
        delay(1500);
        lcd.setCursor(0, 1);
        lcd.print(".");
        delay(1500);
        lcd.print(".");
        delay(1500);
        lcd.print(".");
        delay(3000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Fortune");
        lcd.setCursor(0, 1);
        lcd.print("not found");
        delay(8000);
        lcd.clear();
        lcd.print("Please");
        lcd.setCursor(0, 1);
        lcd.print("step on!");
        break;
        
      case 1:
        delay(1500);
        lcd.print("Your sole says");
        delay(1500);
        lcd.setCursor(0, 1);
        lcd.print(".");
        delay(1500);
        lcd.print(".");
        delay(1500);
        lcd.print(".");
        delay(3000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("You are not");
        lcd.setCursor(0, 1);
        lcd.print("illiterate");
        delay(8000);
        lcd.clear();
        lcd.print("Please");
        lcd.setCursor(0, 1);
        lcd.print("step on!");
        break;
                
      case 2:
        delay(1500);
        lcd.print("Your sole says");
        delay(1500);
        lcd.setCursor(0, 1);
        lcd.print(".");
        delay(1500);
        lcd.print(".");
        delay(1500);
        lcd.print(".");
        delay(1500);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Hmm");
        delay(1000);
        lcd.print(".");
        delay(1000);
        lcd.print(".");
        delay(1000);
        lcd.print(".");
        delay(1000);
        lcd.print("this");
        lcd.setCursor(0, 1);
        lcd.print("is a tricky one");
        delay(3000);
        lcd.clear();
        delay(1500);
        lcd.setCursor(0, 0);
        lcd.print("You'll be");
        lcd.setCursor(0, 1);
        lcd.print("hungary in 1 hr!");
        delay(8000);
        lcd.clear();
        lcd.print("Please");
        lcd.setCursor(0, 1);
        lcd.print("step on!");
        break;
              
      case 3:
        delay(1500);
        lcd.print("Your sole says");
        delay(1500);
        lcd.setCursor(0, 1);
        lcd.print(".");
        delay(1500);
        lcd.print(".");
        delay(1500);
        lcd.print(".");
        delay(3000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Fortune");
        lcd.setCursor(0, 1);
        lcd.print("not found");
        delay(8000);
        lcd.clear();
        lcd.print("Please");
        lcd.setCursor(0, 1);
        lcd.print("step on!");
        break;
        
      case 4:
        delay(1500);
        lcd.print("Your sole says");
        delay(1500);
        lcd.setCursor(0, 1);
        lcd.print(".");
        delay(1500);
        lcd.print(".");
        delay(1500);
        lcd.print(".");
        delay(3000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Your fortune is ");
        lcd.setCursor(0, 1);
        lcd.print("in the cookies");
        delay(8000);
        lcd.clear();
        lcd.print("Please");
        lcd.setCursor(0, 1);
        lcd.print("step on!");
        break;

      case 5:
        delay(1500);
        lcd.print("Your sole says");
        delay(1500);
        lcd.setCursor(0, 1);
        lcd.print(".");
        delay(1500);
        lcd.print(".");
        delay(1500);
        lcd.print(".");
        delay(3000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Meh.");
        delay(2000);
        lcd.setCursor(0, 1);
        lcd.print("Next feet please.");
        delay(5000);
        lcd.clear();
        lcd.print("Please");
        lcd.setCursor(0, 1);
        lcd.print("step on!");
        break;

      case 6:
        delay(1500);
        lcd.print("Your sole says");
        delay(1500);
        lcd.setCursor(0, 1);
        lcd.print(".");
        delay(1500);
        lcd.print(".");
        delay(1500);
        lcd.print(".");
        delay(3000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Call your mother!");
        delay(8000);
        lcd.clear();
        lcd.print("Please");
        lcd.setCursor(0, 1);
        lcd.print("step on!");
        
        break;

      case 7:
        delay(1500);
        lcd.print("Your sole says");
        delay(1500);
        lcd.setCursor(0, 1);
        lcd.print(".");
        delay(1500);
        lcd.print(".");
        delay(1500);
        lcd.print(".");
        delay(3000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Your Gizmo will");
        lcd.setCursor(0, 1);
        lcd.print("be amazing!");
        delay(8000);
        lcd.clear();
        lcd.print("Please");
        lcd.setCursor(0, 1);
        lcd.print("step on!");        
        break;
      }
    }
  }
  // save the current switch state as the last state 
  prevSwitchState = switchState;
}
