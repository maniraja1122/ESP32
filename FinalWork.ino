//
//
//
//void loop(){
//  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)){
//    sendDataPrevMillis = millis();
//    // Write an Int number on the database path test/int
//    if (){
//      Serial.println("PASSED");
//      Serial.println("PATH: " + fbdo.dataPath());
//      Serial.println("TYPE: " + fbdo.dataType());
//    }
//    else {
//      Serial.println("FAILED");
//      Serial.println("REASON: " + fbdo.errorReason());
//    }
//    count++;
//    
//    // Write an Float number on the database path test/float
//    if (Firebase.RTDB.setFloat(&fbdo, "test/float", 0.01 + random(0,100))){
//      Serial.println("PASSED");
//      Serial.println("PATH: " + fbdo.dataPath());
//      Serial.println("TYPE: " + fbdo.dataType());
//    }
//    else {
//      Serial.println("FAILED");
//      Serial.println("REASON: " + fbdo.errorReason());
//    }
//  }
//}

//Main

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
#define API_KEY "AIzaSyDIh1vBj-DPkZ0TNN4WJ4KGcrrj6CIQLH8"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://my-security-c42b7-default-rtdb.firebaseio.com" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

int myout=15;
int pinsound=12;
int pinled=25;
void setup() {
  pinMode(myout,INPUT);
  pinMode(pinsound,OUTPUT);
  pinMode(pinled,OUTPUT);
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
}

void loop() {
  digitalWrite(myout,LOW);
  int stat=digitalRead(myout);
  if(stat==1){
    if (Firebase.ready()){
  Firebase.RTDB.setString(&fbdo, "status/show", "Currently Buzzing");
  Firebase.RTDB.setInt(&fbdo, "check/value",0);
  Serial.println("Firebase Updated");
  }
  digitalWrite(pinled,HIGH);
  digitalWrite(pinsound,HIGH);
  int check=0;
  while(check==0){
    if (Firebase.ready()){
  if (Firebase.RTDB.getInt(&fbdo, "check/value")) {
      if (fbdo.dataType() == "int") {
        check = fbdo.intData();
      }
    }
    }
  }
  digitalWrite(pinled,LOW);
  digitalWrite(pinsound,LOW);
  }
    else{
      Serial.println("no detection");
      digitalWrite(pinsound,LOW);
      if (Firebase.ready()){
   Firebase.RTDB.setString(&fbdo, "status/show", "Nothing to Worry");
   Firebase.RTDB.setInt(&fbdo, "check/value",1);
    Serial.println("Firebase Updated");
  }
    }
}
