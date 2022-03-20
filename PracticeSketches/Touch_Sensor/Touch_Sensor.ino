void setup() {
  Serial.begin(115200);
  Serial.println("Started");
  delay(1000);
}

void loop() {
   if(touchRead(T0)<=50){
    Serial.println("Yellow Line Touched");
   }
   if(touchRead(T3)<=50){
    Serial.println("Brown Line Touched");
   }
   delay(1000);
}
