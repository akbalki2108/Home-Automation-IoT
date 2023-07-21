#define echoPin 19 
#define trigPin 21

long duration;
int distance; 

void ultraSonicSetup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
}
