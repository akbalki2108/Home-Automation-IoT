const int ledPin1 = 15; 
const int ledPin2 = 2;
const int ledPin3 = 4; 

int ledState1 = LOW;   
int ledState2 = LOW;
int ledState3 = LOW;

void ledSetup(){
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
}