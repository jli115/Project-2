// MADE BY VINICIUS LOPES
#include <Ultrasonic.h>
#include "LedControl.h"
#include "binary.h"
Ultrasonic sensor (6,5);// PIN 6 = TRIG // PIN 5 = ECHO
LedControl lc = LedControl(8,10,9,1);// DIN = 8  // CS = 9 // CLK = 10

const int  buttonPin = 2;

int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

unsigned long delaytime=1000;
// PIN 6 = TRIG // PIN 5 = ECHO
// DIN = 8  // CS = 9 // CLK = 10

byte ft[8]= {
  
B00111100,
B01000010,
B10010101,
B10100001,
B10100001,
B10010101,
B01000010,
B00111100


};

byte ff[8]= {
B00111100,
B01000010,
B10100101,
B10010001,
B10010001,
B10100101,
B01000010,
B00111100};

byte fl[8]= {
  B01100110,
  B00111100,
  B01011010,
  B00000000,
  B00111100,
  B01000010,
  B00000000,
  B00000000};

void setup() {
  pinMode(buttonPin, INPUT);
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);  
  Serial.begin(9600);
}

void desenhaFaces(){


}

void loop(){
  
   // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;


  int dist = sensor.Ranging(CM);
  if(dist<40){
    if(buttonPushCounter % 2 == 0) {

    lc.setRow(0,0,fl[0]);
  lc.setRow(0,1,fl[1]);
  lc.setRow(0,2,fl[2]);
  lc.setRow(0,3,fl[3]);
  lc.setRow(0,4,fl[4]);
  lc.setRow(0,5,fl[5]);
  lc.setRow(0,6,fl[6]);
  lc.setRow(0,7,fl[7]);
    }
    else{
      lc.setRow(0,0,ff[0]);
  lc.setRow(0,1,ff[1]);
  lc.setRow(0,2,ff[2]);
  lc.setRow(0,3,ff[3]);
  lc.setRow(0,4,ff[4]);
  lc.setRow(0,5,ff[5]);
  lc.setRow(0,6,ff[6]);
  lc.setRow(0,7,ff[7]);
    }
  }
  else{
      lc.setRow(0,0,ft[0]);
  lc.setRow(0,1,ft[1]);
  lc.setRow(0,2,ft[2]);
  lc.setRow(0,3,ft[3]);
  lc.setRow(0,4,ft[4]);
  lc.setRow(0,5,ft[5]);
  lc.setRow(0,6,ft[6]);
  lc.setRow(0,7,ft[7]);

  }delay(100);

  
  
}
