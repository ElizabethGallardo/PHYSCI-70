


int analogPin = A4;
int analogPin2 = A5; // potentiometer wiper (middle terminal) connected to analog pin 3
                    // outside leads to ground and +5V
int val = 0;  // variable to store the value read
int val2 = 0;

void setup() {
  Serial.begin(9600);           //  setup serial
}

void loop() {
  val = analogRead(analogPin);  // read the input pin
  Serial.print("phototransistor 1 = ");          // debug value
  Serial.println( val);
  val2 = analogRead(analogPin2);  // read the input pin
  Serial.print("phototransistor 2 = ");          // debug value
  Serial.println( val2);
  delay(1000);
}

// random walk
// when it is time to find shade
// checkForShade

// checkForShade()
// read phototransistors - when both read blow 2500 - stop moving
// stay as long as both under 2500, if not start checkForSahde
// below 2500 we are in the shade
// need to calibrate every day - include potentiometer
