#include "LedControl.h"
#include "binary.h"
#include "pitches.h"
#include <NewPing.h>

//Ultrasonic sensor (6,5);// PIN 6 = TRIG // PIN 5 = ECHO
LedControl lc = LedControl(8,10,9,1);// DIN = 8  // CS = 9 // CLK = 10




#define TRIGGER_PIN  6  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     5  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  400, 800, 800, 400, 400, 400, 400, 400
};




const int  buttonPin = 2;

int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

//unsigned long delaytime=1000;
// PIN 6 = TRIG // PIN 5 = ECHO
// DIN = 8  // CS = 9 // CLK = 10

unsigned long time;

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
  B00011110,
  B00111111,
  B01111110,
  B11111100,
  B01111110,
  B00111111,
  B00011110,
  B00000000};

byte fn[8]= {
  B10100000,
  B11100000,
  B10100000,
  B00010000,
  B00011001,
  B00010101,
  B00010011,
  B00010001};
  

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


  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");



  
  int dist = sonar.ping_cm();
  if(dist<50){
          
    for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(7, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
     time = millis();

  Serial.println(time);    //prints time since program started
  delay(1000);         
    //int pauseBetweenNotes = noteDuration * 1.30;
    //delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);}
    if(buttonPushCounter % 2 == 0) {
    lc.setRow(0,0,fl[0]);
  lc.setRow(0,1,fl[1]);
  lc.setRow(0,2,fl[2]);
  lc.setRow(0,3,fl[3]);
  lc.setRow(0,4,fl[4]);
  lc.setRow(0,5,fl[5]);
  lc.setRow(0,6,fl[6]);
  lc.setRow(0,7,fl[7]);}
  
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
    if(buttonPushCounter % 2 == 0) {
  
    lc.setRow(0,0,fn[0]);
  lc.setRow(0,1,fn[1]);
  lc.setRow(0,2,fn[2]);
  lc.setRow(0,3,fn[3]);
  lc.setRow(0,4,fn[4]);
  lc.setRow(0,5,fn[5]);
  lc.setRow(0,6,fn[6]);
  lc.setRow(0,7,fn[7]);
    }else{
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
}
