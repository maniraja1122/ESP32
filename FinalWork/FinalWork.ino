#define RXD2 16
#define TXD2 17

#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "mani"
#define WIFI_PASSWORD "12345678"

// Insert Firebase project API Key
#define API_KEY "AIzaSyArWtqhQpSI9ZZVcxOLXg8Mu3SWMyLWl2A"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://control-app-9077c-default-rtdb.firebaseio.com" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

bool signupOK = false;
/* Variables Used */


void setup(){
 Serial.begin(115200);
  Serial2.begin(9600,SERIAL_8N1,RXD2,TXD2);
 Serial.begin(115200);
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
   if(Firebase.ready() && signupOK){
    Firebase.RTDB.setString(&fbdo, "glucovalue",Serial2.readString());
  }
}

void loop(){
  Serial.println(Serial2.readString());
  if(Firebase.ready() && signupOK){
    Firebase.RTDB.setString(&fbdo, "glucovalue",Serial2.readString());
  }
  delay(200);
}
