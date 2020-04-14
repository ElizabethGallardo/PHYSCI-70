#include <WiFi.h>                                 // esp32 library
#include <FirebaseESP32.h>                        // firebase library

#define FIREBASE_HOST "https://thispool-islit.firebaseio.com"                 // the project name address from firebase id
#define FIREBASE_AUTH "A6N4gaqv6Q0sKA5Ng5RRmYnXZl4H5N0A0gyFlwP8"              // the secret key generated from firebase
#define WIFI_SSID "epistek"                                                   // input your home or public wifi name
#define WIFI_PASSWORD "9542353260"                                            // password of wifi ssid

String fireString = "";                                                       // led status received from firebase
int fireInt = 0;
int ledpin = 5;


// Set up the rgb led names
uint8_t ledR = 4;
uint8_t ledG = 5;
uint8_t ledB = 18;

uint8_t ledArray[3] = {1, 2, 3}; // three led channels

const boolean invert = true; // set true if common anode, false if common cathode

uint8_t color = 0;           // a value from 0 to 255 representing the hue
uint32_t R, G, B;            // the Red Green and Blue color components
uint8_t brightness = 255;    // 255 is maximum brightness, but can be changed.  Might need 256 for common anode to fully turn off.


//Define FirebaseESP32 data object
FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);
  delay(1000);

  ledcAttachPin(ledR, 1); // assign RGB led pins to channels
  ledcAttachPin(ledG, 2);
  ledcAttachPin(ledB, 3);

  // Initialize channels
  // channels 0-15, resolution 1-16 bits, freq limits depend on resolution
  // ledcSetup(uint8_t channel, uint32_t freq, uint8_t resolution_bits);
  ledcSetup(1, 12000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(2, 12000, 8);
  ledcSetup(3, 12000, 8);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                          // try to connect with wifi

  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                // print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                  // connect to firebase
  Firebase.reconnectWiFi(true);
  Firebase.set(firebaseData, "/LED_INTENSITY", "100");          // set initial string of "100"
  Firebase.set(firebaseData, "/LED_RED", "0");                  // set initial string "0" is off
  Firebase.set(firebaseData, "/LED_GREEN", "0");                // set initial string "0" is off
  Firebase.set(firebaseData, "/LED_BLUE", "0");                 // set initial string of "0" is off
}

void loop() {

  Firebase.get(firebaseData, "/LED_RED");                      // get led_red input from firebase
  fireString = firebaseData.stringData();                      // change to e.g. intData() or boolData()
  Serial.println("R: " + fireString);
  ledcWrite(1, fireString.toInt());
  delay(100);

  Firebase.get(firebaseData, "/LED_GREEN");                      // get led_red input from firebase
  fireString = firebaseData.stringData();                      // change to e.g. intData() or boolData()
  Serial.println("G: " + fireString);
  ledcWrite(2, fireString.toInt());
  delay(100);

  Firebase.get(firebaseData, "/LED_BLUE");                      // get led_red input from firebase
  fireString = firebaseData.stringData();                      // change to e.g. intData() or boolData()
  Serial.println("B: " + fireString);
  ledcWrite(3, fireString.toInt());
  delay(100);
  //
  //  Serial.println("Starting color fade loop.");
  //
  // for (color = 0; color < 255; color++) { // Slew through the color spectrum
  //
  //  hueToRGB(color, brightness);  // call function to convert hue to RGB
  //
  //  // write the RGB values to the pins
  //  ledcWrite(1, R); // write red component to channel 1, etc.
  //  ledcWrite(2, G);
  //  ledcWrite(3, B);
  //
  //delay(10000); // full cycle of rgb over 256 colors takes 26 seconds
  // }
}

// Courtesy http://www.instructables.com/id/How-to-Use-an-RGB-LED/?ALLSTEPS
// function to convert a color to its Red, Green, and Blue components.

void hueToRGB(uint8_t hue, uint8_t brightness)
{
  uint16_t scaledHue = (hue * 6);
  uint8_t segment = scaledHue / 256; // segment 0 to 5 around the
  // color wheel
  uint16_t segmentOffset =
    scaledHue - (segment * 256); // position within the segment

  uint8_t complement = 0;
  uint16_t prev = (brightness * ( 255 -  segmentOffset)) / 256;
  uint16_t next = (brightness *  segmentOffset) / 256;

  if (invert)
  {
    brightness = 255 - brightness;
    complement = 255;
    prev = 255 - prev;
    next = 255 - next;
  }

  switch (segment ) {
    case 0:      // red
      R = brightness;
      G = next;
      B = complement;
      break;
    case 1:     // yellow
      R = prev;
      G = brightness;
      B = complement;
      break;
    case 2:     // green
      R = complement;
      G = brightness;
      B = next;
      break;
    case 3:    // cyan
      R = complement;
      G = prev;
      B = brightness;
      break;
    case 4:    // blue
      R = next;
      G = complement;
      B = brightness;
      break;
    case 5:      // magenta
    default:
      R = brightness;
      G = complement;
      B = prev;
      break;
  }
}
