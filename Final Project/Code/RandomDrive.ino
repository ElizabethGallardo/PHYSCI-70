/*
 Bidirectional motor driver uses the dual H-bridge driver module.
 Inputs to the module on pins 9 and 10.
 VCC on the driver module connected to Vin on the Arduino board.
 GND on the module to GND on the Arduino.

 Driver channels are fully on when inputs are LOW.
 If you need variable speed, use analogWrite.
 
 
  This example code is in the public domain.
*/

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
 delay(oneYardTime);
 
   // TURN LEFT
digitalWrite(bwd1, HIGH);  //  Turn off backward input.
digitalWrite(fwd1, LOW);   // Turn on motor forward.
digitalWrite(bwd2, LOW);  //  Turn off backward input.
digitalWrite(fwd2, HIGH);   // Turn off motor forward.
 delay(turningTime);

   // MOVE FORWARD
digitalWrite(fwd1, HIGH);  //  Turn off forward input.
digitalWrite(bwd1, LOW);   // Turn on motor backwards.  
digitalWrite(fwd2, HIGH);  //  Turn off forward input.
digitalWrite(bwd2, LOW);   // Turn on motor backwards.
 delay(oneYardTime);

   // TURN RIGHT
digitalWrite(bwd1, LOW);  //  Turn off backward input.
digitalWrite(fwd1, HIGH);   // Turn on motor forward.
digitalWrite(bwd2, HIGH);  //  Turn off backward input.
digitalWrite(fwd2, LOW);   // Turn off motor forward.
 delay(turningTime);
 

   // MOVE FORWARD
digitalWrite(fwd1, HIGH);  //  Turn off forward input.
digitalWrite(bwd1, LOW);   // Turn on motor backwards.  
digitalWrite(fwd2, HIGH);  //  Turn off forward input.
digitalWrite(bwd2, LOW);   // Turn on motor backwards.
 delay(oneYardTime);


   // TURN RIGHT
digitalWrite(bwd1, LOW);  //  Turn off backward input.
digitalWrite(fwd1, HIGH);   // Turn on motor forward.
digitalWrite(bwd2, HIGH);  //  Turn off backward input.
digitalWrite(fwd2, LOW);   // Turn off motor forward.
 delay(turningTime);

   // MOVE BACKWARD
digitalWrite(bwd1, HIGH);  //  Turn off backward input.
digitalWrite(fwd1, LOW);   // Turn on motor forward.
digitalWrite(bwd2, HIGH);  //  Turn off backward input.
digitalWrite(fwd2, LOW);   // Turn on motor forward.
 delay(oneYardTime);

  
}
