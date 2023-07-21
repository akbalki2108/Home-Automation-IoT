//butoon
const int buttonPin1 = 13;
const int buttonPin2 = 12;
const int buttonPin3 = 14;
const int buttonPin4 = 27;
const int buttonPin5 = 26;


int buttonState1;
int buttonState2;  
int buttonState3;          

int lastButtonState1 = LOW;  
int lastButtonState2 = LOW; 
int lastButtonState3 = LOW; 


//button press response
unsigned long lastDebounceTime1 = 0;  
unsigned long lastDebounceTime2 = 0;  
unsigned long lastDebounceTime3 = 0;

unsigned long debounceDelay = 50;

void buttonSetup(){
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
}

void handleButton() {
  digitalWrite(ledPin1, ledState1);
  digitalWrite(ledPin2, ledState2);
  digitalWrite(ledPin3, ledState3);
}

void buttonFxn() {
  int reading1 = digitalRead(buttonPin1);
  int reading2 = digitalRead(buttonPin2);
  int reading3 = digitalRead(buttonPin3);
  
  if (reading1 != lastButtonState1) {
    lastDebounceTime1 = millis();
  }
  if (reading2 != lastButtonState2) {
    lastDebounceTime2 = millis();
  }
  if (reading3 != lastButtonState3) {
    lastDebounceTime3 = millis();
  }

  if ((millis() - lastDebounceTime1) > debounceDelay) {
    if (reading1 != buttonState1) {
      buttonState1 = reading1;
      if (buttonState1 == LOW) {
        ledState1 = !ledState1;
      }
    }
  }

  if ((millis() - lastDebounceTime2) > debounceDelay) {
    if (reading2 != buttonState2) {
      buttonState2 = reading2;
      if (buttonState2 == LOW) {
        ledState2 = !ledState2;
      }
    }
  }

  if ((millis() - lastDebounceTime3) > debounceDelay) {
    if (reading3 != buttonState3) {
      buttonState3 = reading3;
      if (buttonState3 == LOW) {
        ledState3 = !ledState3;
      }
    }
  }

  handleButton();
  
  lastButtonState1 = reading1;
  lastButtonState2 = reading2;
  lastButtonState3 = reading3;

}


