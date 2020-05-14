
int photoPin = A4;
int photoPin2 = A5; 
int val = 0;                        // variable to store the value read
int val2 = 0;
const int transistorCalib = 3500;  
  // MOTOR 1
const int bwd1 = 15;               //Choose your digital IO pins as appropriate to your board.
const int fwd1 = 32;
  // MOTOR 2
const int bwd2 = 26;               //Choose your digital IO pins as appropriate to your board.
const int fwd2 = 25; 

void setup() {
  Serial.begin(9600);    //  setup serial
  pinMode(photoPin, INPUT);
  pinMode(photoPin2, INPUT);
  pinMode(fwd1, OUTPUT); //set pin  as an output pin.
  pinMode(bwd1, OUTPUT); //set pin   as an output pin.    
  pinMode(fwd2, OUTPUT); //set pin  as an output pin.
  pinMode(bwd2, OUTPUT); //set pin   as an output pin.
}

void loop() {
  // random walk
    // MOVE FORWARD
  digitalWrite(fwd1, HIGH);  //  Turn off forward input.
  digitalWrite(bwd1, LOW);   // Turn on motor backwards.  
  digitalWrite(fwd2, HIGH);  //  Turn off forward input.
  digitalWrite(bwd2, LOW);   // Turn on motor backwards.
  Serial.println("Time to find shade!");
  // when it is time to find shade
  // checkForShade
  checkForShade(transistorCalib);
  delay(1000);
}


void checkForShade(int transistorCalib){
  val = analogRead(photoPin);                   // read the input pin
  Serial.print("phototransistor 1 = ");          // debug value
  Serial.println( val);
  val2 = analogRead(photoPin2);                 // read the input pin
  Serial.print("phototransistor 2 = ");          // debug value
  Serial.println( val2);
  
  while (val < transistorCalib && val2 < transistorCalib) {           // while both phototransistors read blow calibrated value - stop moving
        // STOP MOVING
        Serial.println("I found shade!");  
        digitalWrite(bwd1, HIGH);   //  Turn off backward input.
        digitalWrite(fwd1, HIGH);   // Turn off motor forward.
        digitalWrite(bwd2, HIGH);   //  Turn off backward input.
        digitalWrite(fwd2, HIGH);   // Turn off motor forward.
        val = analogRead(photoPin); 
        val2 = analogRead(photoPin2); 
        delay(1000);
    }
}
