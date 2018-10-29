#include <LedControl.h>
int ANIMDELAY = 100;  // animation delay, deafault value is 100
int INTENSITYMIN = 0; // minimum brightness, valid range [0,15]
int INTENSITYMAX = 8; // maximum brightness, valid range [0,15]
int potPin= A0;  //Declare potPin to be analog pin A0
int DIN_PIN = 8;      // data in pin
int CS_PIN = 9;       // load (CS) pin
int CLK_PIN = 10;      // clock pin
// MAX7219 registers
byte MAXREG_DECODEMODE = 0x09;
byte MAXREG_INTENSITY  = 0x0a;
byte MAXREG_SCANLIMIT  = 0x0b;
byte MAXREG_SHUTDOWN   = 0x0c;
byte MAXREG_DISPTEST   = 0x0f;

const unsigned char heart[] =
{
  B01100110,
  B11111111,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00011000,
  B00000000
};



void setup ()
{
  pinMode(DIN_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(CS_PIN, OUTPUT);

  // initialization of the MAX7219
  setRegistry(MAXREG_SCANLIMIT, 0x07);
  setRegistry(MAXREG_DECODEMODE, 0x00);  // using an led matrix (not digits)
  setRegistry(MAXREG_SHUTDOWN, 0x01);    // not in shutdown mode
  setRegistry(MAXREG_DISPTEST, 0x00);    // no display test
  setRegistry(MAXREG_INTENSITY, 0x0f & INTENSITYMIN);

  // draw hearth
  setRegistry(1, heart[0]);
  setRegistry(2, heart[1]);
  setRegistry(3, heart[2]);
  setRegistry(4, heart[3]);
  setRegistry(5, heart[4]);
  setRegistry(6, heart[5]);
  setRegistry(7, heart[6]);
  setRegistry(8, heart[7]);
}


void loop ()
{
  // second beat
  setRegistry(MAXREG_INTENSITY, 0x0f & INTENSITYMAX);
  delay(ANIMDELAY);
  
  // switch off
  setRegistry(MAXREG_INTENSITY, 0x0f & INTENSITYMIN);
  delay(ANIMDELAY);
  
  // second beat
  setRegistry(MAXREG_INTENSITY, 0x0f & INTENSITYMAX);
  delay(ANIMDELAY);
  
  // switch off
  setRegistry(MAXREG_INTENSITY, 0x0f & INTENSITYMIN);
  delay(ANIMDELAY*6);
}


void setRegistry(byte reg, byte value)
{
  digitalWrite(CS_PIN, LOW);

  putByte(reg);   // specify register
  putByte(value); // send data

  digitalWrite(CS_PIN, LOW);
  digitalWrite(CS_PIN, HIGH);
}

void putByte(byte data)
{
  byte i = 8;
  byte mask;
  while (i > 0)
  {
    mask = 0x01 << (i - 1);        // get bitmask
    digitalWrite( CLK_PIN, LOW);   // tick
    if (data & mask)               // choose bit
      digitalWrite(DIN_PIN, HIGH); // send 1
    else
      digitalWrite(DIN_PIN, LOW);  // send 0
    digitalWrite(CLK_PIN, HIGH);   // tock
    --i;                           // move to lesser bit
  }
}
/*
int DIN = 8;
int CS =  9;
int CLK = 10;
LedControl lc=LedControl(DIN,CLK,CS,0);

int readValue;  // Use this variable to read Potentiometer
int writeValue; // Use this variable for writing to LED

byte e[8]=     {0x7C,0x7C,0x60,0x7C,0x7C,0x60,0x7C,0x7C};
byte d[8]=     {0x78,0x7C,0x66,0x66,0x66,0x66,0x7C,0x78};
byte u[8]=     {0x66,0x66,0x66,0x66,0x66,0x66,0x7E,0x7E};
byte c[8]=     {0x7E,0x7E,0x60,0x60,0x60,0x60,0x7E,0x7E};
byte eight[8]= {0x7E,0x7E,0x66,0x7E,0x7E,0x66,0x7E,0x7E};
byte s[8]=     {0x7E,0x7C,0x60,0x7C,0x3E,0x06,0x3E,0x7E};
byte dot[8]=   {0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18};
byte o[8]=     {0x7E,0x7E,0x66,0x66,0x66,0x66,0x7E,0x7E};
byte m[8]=     {0xE7,0xFF,0xFF,0xDB,0xDB,0xDB,0xC3,0xC3};


void setup() {
  pinMode(potPin, INPUT);  //set potPin to be an input
 lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
 lc.setIntensity(0,15);      // Set the brightness to maximum value
 lc.clearDisplay(0);         // and clear the display
  Serial.begin(9600);      // turn on Serial Port
}
 
void loop() {
  
 readValue = analogRead(potPin);  //Read the voltage on the Potentiometer
 writeValue = (255./1023.) * readValue; //Calculate Write Value for LED
 analogWrite(DIN, writeValue); 
  analogWrite(CS, writeValue); 
   analogWrite(CLK, writeValue); 
 Serial.print("You are writing a value of ");  //for debugging print your values
 Serial.println(writeValue);
 
}*/
