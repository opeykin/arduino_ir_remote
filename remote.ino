#include <IRremote.h>
#include <IRremoteInt.h>


const int powerPin = 5;
const int sourcePin = 4;
const int ledPin =  13;
const int dataPin = 3;


int powerState = LOW;
int sourceState = LOW;

unsigned int powerData[] = {4600,4350,700,1550,650,1550,650,1600,650,450,650,450,650,450,650,450,700,400,700,1550,650,1550,650,1600,650,450,650,450,650,450,700,450,650,450,650,450,650,1550,700,450,650,450,650,450,650,450,650,450,700,400,650,1600,650,450,650,1550,650,1600,650,1550,650,1550,700,1550,650,1550,650};
unsigned int sourceData[]  = {4600,4350,700,1550,650,1550,700,1500,700,450,650,450,700,400,700,400,700,400,700,1550,700,1500,700,1550,700,400,700,400,700,400,700,400,700,400,700,1550,700,400,700,450,650,450,650,450,700,400,700,400,700,400,700,450,650,1550,700,1500,700,1550,650,1550,700,1500,700,1550,700,1500,700};

const int frequency = 38;
const int cmdLength = 68;


IRsend irsend;


void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(powerPin, INPUT);
  pinMode(sourcePin, INPUT);
}

bool checkButton(int& state, const int pin)
{
  int newState = digitalRead(pin);
  boolean result = (state == LOW) && (newState == HIGH);
  state = newState;
  return result;  
}

void sendDataIfPressed(int& state, const int pin, unsigned int data[])
{
  if (checkButton(state, pin))
  {
    digitalWrite(ledPin, HIGH);
    irsend.sendRaw(data, cmdLength, frequency);
    delay(500);
    digitalWrite(ledPin, LOW);
  }
}

void loop() {
  sendDataIfPressed(powerState, powerPin, powerData);
  sendDataIfPressed(sourceState, sourcePin, sourceData); 
}
