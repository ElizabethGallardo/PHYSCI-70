/*
 * Code written by: Elizabeth GH
 * 02/24/2020
 */


#define RED_LEDs 7
#define LED_GREEN_1 9
#define LED_GREEN_2 10
#define LED_GREEN_3 11
#define BUTTON 12

void setup() {
  // // put your setup code here, to run once:
  
  // initialize digital pins 
  pinMode(LED_GREEN_1, OUTPUT); // pin 9
  pinMode(LED_GREEN_2, OUTPUT); // pin 10
  pinMode(LED_GREEN_3, OUTPUT); // pin 11
  pinMode(RED_LEDs, OUTPUT);    // all RED LEDs
  pinMode(BUTTON, INPUT);

}

void loop() {
  // // put your main code here, to run repeatedly:
  
  int butt = 0;
  butt = digitalRead(BUTTON);
  if (butt == HIGH)
  {
      //Turning ON LEDs sequentially:
      digitalWrite(LED_GREEN_1, HIGH);   // turn ON GREEN LED 1
      delay(250);                        // wait for a 250 ms
      
      int val = 0;
      val = digitalRead(LED_GREEN_1);
      if (val == HIGH) 
      { 
      digitalWrite(LED_GREEN_2, HIGH);   // turn ON GREEN LED 2
      delay(250);                       
 
      val = digitalRead(LED_GREEN_2);
      if (val == HIGH)
      {
      digitalWrite(LED_GREEN_3, HIGH);   // turn ON GREEN LED 3
      delay(250);                        
      digitalWrite(LED_GREEN_1, LOW); 
      digitalWrite(LED_GREEN_2, LOW); 
      digitalWrite(LED_GREEN_3, LOW);
      delay(250); 
      }
      }
   }

  if (butt == LOW) 
  {  
      digitalWrite(LED_GREEN_1, LOW); 
      digitalWrite(LED_GREEN_2, LOW); 
      digitalWrite(LED_GREEN_3, LOW); 
      digitalWrite(RED_LEDs, HIGH);   // turn ON all RED LEDs
      delay(2500);                    // wait for a second
      digitalWrite(RED_LEDs, LOW);    // turn the LED off by making the voltage LOW
      delay(500); 
  }

}
