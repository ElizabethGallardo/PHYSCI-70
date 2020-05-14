// the number of the LED pin
const int ledPin = 15;  // 15 corresponds to GPIO15

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
 
void setup(){
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel);
}
 
void loop(){
  // increase the Motor Speed
  for(int dutyCycle = 0; dutyCycle <= 150; dutyCycle++){   //255
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);
    Serial.print(dutyCycle);
    delay(15);
  }

  // decrease the Motor Speed
  for(int dutyCycle = 150; dutyCycle >= 0; dutyCycle--){
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);   
    delay(15);
  }
}
