/*
HC-SR04 Ping distance sensor]
VCC to arduino 5v GND to arduino GND
Echo to Arduino pin 13 Trig to Arduino pin 12
Red POS to Arduino pin 11
Green POS to Arduino pin 10
560 ohm resistor to both LED NEG and GRD power rail
More info at: http://goo.gl/kJ8Gl
Original code improvements to the Ping sketch sourced from Trollmaker.com
Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/

//#define trigPin 27   //%% change here depending on your wiring
//#define echoPin 33   //%% change here depending on your wiring
//#define trigPin 15   //%% change here depending on your wiring
//#define echoPin 32   //%% change here depending on your wiring
int led;
int led2;
int trigPin1 = 27;
int echoPin1 = 33;
int trigPin2 = 12;
int echoPin2 = 13;
  // MOTOR 1
  const int bwd1 = 15;    //Choose your digital IO pins as appropriate to your board.
  const int fwd1 = 32;
  // MOTOR 2
  const int bwd2 = 26;    //Choose your digital IO pins as appropriate to your board.
  const int fwd2 = 25;
  //Turning parameters
  const int turningTime = 3000; // in milliseconds. This is 3 seconds.
  const int oneYardTime = 10000; // 10 seconds


void setup() {
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
    pinMode(fwd1, OUTPUT); //set pin  as an output pin.
    pinMode(bwd1, OUTPUT); //set pin   as an output pin.
    pinMode(fwd2, OUTPUT); //set pin  as an output pin.
    pinMode(bwd2, OUTPUT); //set pin   as an output pin.
}

void loop() {
    // MOVE FORWARD
  digitalWrite(fwd1, HIGH);  //  Turn off forward input.
  digitalWrite(bwd1, LOW);   // Turn on motor backwards.  
  digitalWrite(fwd2, HIGH);  //  Turn off forward input.
  digitalWrite(bwd2, LOW);   // Turn on motor backwards.
  delay(1000);
  CheckForCollision(trigPin1, echoPin1);
//  CheckForCollision(trigPin2, echoPin2);

}

void CheckForCollision(int trigPin, int echoPin) {
  long duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10); 
delayMicroseconds(100);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print("Object is ");
  Serial.print(distance); 
  Serial.println(" cm away"); 
  if (distance < 10 && distance != 0) {              
    digitalWrite(led,HIGH);           // If about to collide. turn LED lights RED ON. 
    digitalWrite(led2,LOW);   
    Serial.println("Avoiding collision");         
    avoidCollision(trigPin, echoPin);
}
  else {
    digitalWrite(led,LOW);
    digitalWrite(led2,HIGH);
    Serial.println("No obstacles"); 
  }
  if (distance >= 200 || distance <= 0){
    Serial.println("No obstacles (Out of range)");   // If nothing is in the way. turn LED ligths GREEN ON.
  }
  else {
    Serial.print("Object is ");
    Serial.print(distance);           // If close to object but not about to collide. turn LED lights WHITE ON. 
    Serial.println(" cm away");
  }
  // delay(500);
}


void avoidCollision(int trigPin, int echoPin) {
    // MOVE BACKWARD
  digitalWrite(bwd1, HIGH);  //  Turn off backward input.
  digitalWrite(fwd1, LOW);   // Turn on motor forward.
  digitalWrite(bwd2, HIGH);  //  Turn off backward input.
  digitalWrite(fwd2, LOW);   // Turn on motor forward.
   delay(2000);
 
     // TURN LEFT
  digitalWrite(bwd1, HIGH);  //  Turn off backward input.
  digitalWrite(fwd1, LOW);   // Turn on motor forward.
  digitalWrite(bwd2, LOW);  //  Turn off backward input.
  digitalWrite(fwd2, HIGH);   // Turn off motor forward.
   delay(turningTime);
   
     //  CHECK FOR COLLISIONS
   CheckForCollision(trigPin, echoPin);
}
