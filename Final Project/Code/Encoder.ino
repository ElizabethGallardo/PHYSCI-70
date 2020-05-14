

int encoderA1 = 15;
int encoderA2 = 32; // potentiometer wiper (middle terminal) connected to analog pin 3
                    // outside leads to ground and +5V
int encoderA1_val = 0;  // variable to store the value read
int encoderA2_val = 0;

void setup() {
  Serial.begin(9600);           //  setup serial
  pinMode(encoderA1, INPUT);
  pinMode(encoderA2, INPUT);
}

void loop() {
  encoderA2_val= digitalRead(encoderA2);  // read the input pin
  Serial.print("Encoder A2 =  ");          // debug value
  Serial.println( encoderA2_val);
  encoderA1_val = digitalRead(encoderA1);  // read the input pin
  Serial.print("Encoder A1 =  ");          // debug value
  Serial.println( encoderA1_val);
  delay(250);
}
