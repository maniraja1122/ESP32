int arr[]={21,22,4,15,2,19,18};
int segCode[10][8] = {
{ 1, 1, 1, 1, 1, 1, 0, 0}, //Decimal Digit  0
{ 0, 1, 1, 0, 0, 0, 0, 0}, //Decimal Digit 1
{ 1, 1, 0, 1, 1, 0, 1, 0}, //Decimal Digit 2
{ 1, 1, 1, 1, 0, 0, 1, 0}, //Decimal Digit 3
{ 0, 1, 1, 0, 0, 1, 1, 0}, //Decimal Digit 4
{ 1, 0, 1, 1, 0, 1, 1, 0}, //Decimal Digit 5
{ 1, 0, 1, 1, 1, 1, 1, 0}, //Decimal Digit  6
{ 1, 1, 1, 0, 0, 0, 0, 0}, //Decimal Digit 7
{ 1, 1, 1, 1, 1, 1, 1, 0}, //Decimal Digit 8
{ 1, 1, 1, 1, 0, 1, 1, 0} //Decimal Digit 9
};
int dig[]={12,14,27,26};
int selected=0;
int selectdig=0;
void setup() {
  for(int i=0;i<7;i++){
    pinMode(arr[i], OUTPUT);
  }
  for(int i=0;i<4;i++){
    pinMode(dig[i], OUTPUT);
  }
}

void loop() {
  for(int i=0;i<7;i++){
    digitalWrite(arr[i], HIGH);
  }
  digitalWrite(dig[selectdig], HIGH);
  for(int i=0;i<7;i++){
    if(segCode[selected][i]==1)
    digitalWrite(arr[i], LOW);
  }
  selected++;
  selected%=10;
  selectdig++;
  selectdig%=4;
  delay(1000);
}
