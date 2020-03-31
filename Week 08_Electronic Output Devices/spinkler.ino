// SPRINKLER SYSTEM 
// last updated: March 31 2020

// REFERENCES:
// interrupts: https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
// delays: https://www.arduino.cc/reference/en/language/functions/time/delay/


int smallValve = 0;   
const byte interruptPin = 13;
const byte largeValvePin = 7;
const byte smallValvePin = 9;
volatile byte toggleButtonState = HIGH;

void setup() {
  pinMode(largeValvePin, OUTPUT);           // pin 7 and 8 are digital pins attached to the FET gate.
  pinMode(smallValvePin, OUTPUT); 
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), toggleButtonISR , FALLING);
}

void loop() {
  if (toggleButtonState==HIGH)
  { 
 digitalWrite(largeValvePin, HIGH);
 digitalWrite(smallValvePin, HIGH);
 // delay(pow(4.32,7))                          //  4.32e+7 (Max delay = 4,294,967,295 ms)
 delay(1500);
 digitalWrite(smallValvePin, LOW);
 delay(pow(1500, 1));                             // delay 10 minutes - 600000 ms
 digitalWrite(largeValvePin, LOW);
 delay(500);  
  }
}

void toggleButtonISR() {
  toggleButtonState = !toggleButtonState;
}
