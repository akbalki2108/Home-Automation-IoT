const int fanPin1 = 34; 
const int fanPin2 = 35; 

int fanState1 = LOW;
int fanState2 = LOW; 

void fanSetup(){
  
  pinMode(fanPin1, OUTPUT);
  pinMode(fanPin2, OUTPUT);

  digitalWrite(fanPin1, LOW);
  digitalWrite(fanPin2, LOW);
}
