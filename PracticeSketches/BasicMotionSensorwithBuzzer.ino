int myvcc=23;
int myout=15;
int pinled=12;
void setup() {
  pinMode(myvcc,OUTPUT);
  pinMode(myout,INPUT);
  pinMode(pinled,OUTPUT);
}

void loop() {
  digitalWrite(myvcc,HIGH);
  int stat=digitalRead(myout);
  
  if(stat==HIGH){
    for(int i=0;i<5;i++){
    digitalWrite(pinled,HIGH);
    delay(1000);
    digitalWrite(pinled,LOW);
    delay(1000);
    }
  }
    else{
      digitalWrite(pinled,LOW);
    }
}
