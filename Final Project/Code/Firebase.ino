#include <WiFi.h>                                 // esp32 library
#include <FirebaseESP32.h>                        // firebase library
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define FIREBASE_HOST "esp32-test-70549.firebaseio.com/"  // the project name address from firebase id
#define FIREBASE_AUTH "47T5yQFxpumI3jppODDnmQSnAMBXSh9U4AUyuw07"                          // the secret key generated from firebase
#define WIFI_SSID "epistek"                               // input your home or public wifi name
#define WIFI_PASSWORD "9542353260"                        // password of wifi ssid

#define WEATHER_API_URL "https://api.weather.gov/points/{latitude},{longitude}";
#define TIME_API_URL "http://worldtimeapi.org/api/timezone/{timezone}";

String weatherApiUrl = "";
String forecastApiUrl = "";
String timeApiUrl = "";
String fireString = "";                                          // led status received from firebase
int ledpin = 13;

//Define FirebaseESP32 data object
FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(ledpin, OUTPUT);
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
  Firebase.set(firebaseData, "/LED_STATUS", "OFF");              // set initial string of "OFF"
  Firebase.set(firebaseData, "/WIFI_SSID", WIFI_SSID);
  Firebase.set(firebaseData, "/IP_ADDRESS", IpAddress2String(WiFi.localIP()));

  weatherApiUrl = WEATHER_API_URL;
  Firebase.get(firebaseData, "/_USER_LATITUDE");
  fireString = firebaseData.stringData();
  weatherApiUrl.replace("{latitude}", fireString);
  Firebase.get(firebaseData, "/_USER_LONGITUDE");
  fireString = firebaseData.stringData();
  weatherApiUrl.replace("{longitude}", fireString);
  Serial.println(weatherApiUrl);

  DynamicJsonDocument doc = GetApiJson(weatherApiUrl, 10000);
  if (!doc.isNull()) {
    const char* forecastUrl = doc["properties"]["forecast"];
    Serial.println(forecastUrl);
    forecastApiUrl = String(forecastUrl);
  } else {
    Serial.println("Error retrieving weather forecast Url");
  }
  timeApiUrl = TIME_API_URL;
  Firebase.get(firebaseData, "/_USER_TIMEZONE");
  fireString = firebaseData.stringData();
  timeApiUrl.replace("{timezone}", fireString);
  Serial.println(timeApiUrl);
}

void loop() {

  Firebase.get(firebaseData, "/LED_STATUS");                     // get led status input from firebase
  fireString = firebaseData.stringData();                        // change to e.g. intData() or boolData()
  //Serial.println(fireString);

  if (fireString == "ON") {                    // compare the input of led status received from firebase
    Serial.println("Led Turned ON");
    digitalWrite(ledpin, HIGH);                // make output led ON
  }

  else if (fireString == "OFF") {              // compare the input of led status received from firebase
    Serial.println("Led Turned OFF");
    digitalWrite(ledpin, LOW);                 // make output led OFF
  }

  else {
    Serial.println("Please send ON/OFF");
  }

  DynamicJsonDocument doc = GetApiJson(forecastApiUrl, 20000);
  if (!doc.isNull()) {
    const int temp = doc["properties"]["periods"][0]["temperature"];
    const char* unit = doc["properties"]["periods"][0]["temperatureUnit"];
    const char* forecast = doc["properties"]["periods"][0]["shortForecast"];

    Serial.print("Current Temperature is ");
    Serial.print(temp);
    Serial.print(unit);

    Firebase.set(firebaseData, "/TEMPERATURE", String(temp) + unit);
    Firebase.set(firebaseData, "/FORECAST", forecast);
  } else {
    Serial.println("Error retrieving weather information");
  }

  DynamicJsonDocument docTime = GetApiJson(timeApiUrl, 10000);
  if (!docTime.isNull()) {
    const char* currentTime = docTime["datetime"];
    const long unixTime = docTime["unixtime"];
    Serial.print(currentTime);
    Serial.print(String(unixTime));
    Firebase.set(firebaseData, "/CURRENT_TIME", currentTime);
    Firebase.set(firebaseData, "/CURRENT_UNIXTIME", String(unixTime));
  } else {
    Serial.println("Error retrieving current time");
  }

  delay(1000);                                 // not strictly necessary
}

String IpAddress2String(const IPAddress& ipAddress)
{
  return String(ipAddress[0]) + String(".") + \
         String(ipAddress[1]) + String(".") + \
         String(ipAddress[2]) + String(".") + \
         String(ipAddress[3])  ;
}

DynamicJsonDocument GetApiJson(String endpoint, int bufferSize)
{
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status

    HTTPClient http;
    http.begin(endpoint);       //Specify the URL
    int httpCode = http.GET();  //Make the request

    if (httpCode = 200) {         //Check for the returning code
      String payload = http.getString();
      //Serial.println(httpCode);
      //Serial.println(payload);

      DynamicJsonDocument doc(bufferSize); // Create a buffer of bufferSize bytes
      // Deserialize the JSON document
      DeserializationError error = deserializeJson(doc, payload);

      // Test if parsing succeeds.
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
      }
      http.end();           //Free the resources
      return doc;
    }
    else {
      Serial.println("Error on HTTP request");
    }
    http.end();             //Free the resources
  }
  DynamicJsonDocument docEmpty(1);
  return docEmpty;
}
