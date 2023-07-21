#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

#include "wifiFile.h"
#include "led.h"
#include "fan.h"
#include "button.h"
#include "ultraSonic.h"
#include "dht11.h"
#include "index.h"

AsyncWebServer server(80);

void setup() {

  
  Serial.begin(115200);

  //light
  ledSetup();
  fanSetup();
  buttonSetup();
  ultraSonicSetup();
  dht11Setup();
  

  //wifi
  Serial.println("Booting/...");
  wifiSetup();
  
  server.on("/", HTTP_GET, handleRoot);
  server.on("/status", HTTP_GET, handleStatus);

  server.on("/led1Update", HTTP_GET, handleLed1);
  server.on("/led2Update", HTTP_GET, handleLed2);
  server.on("/led3Update", HTTP_GET, handleLed3);

  server.on("/fan1Update", HTTP_GET, handleFan1);
  server.on("/fan2Update", HTTP_GET, handleFan2);
  
  server.on("/distance", HTTP_GET, handleUltraSonic);
  server.on("/dht11", HTTP_GET, handleDht11);

  server.on("/led/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin1, HIGH);
    request->send(200, "text/plain", "LED on");
  });

  server.on("/led/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin1, LOW);
    request->send(200, "text/plain", "LED off");
  });



  server.begin();
}

void loop() {
  buttonFxn();
}

void handleRoot(AsyncWebServerRequest *request) {
  request->send(200, "text/html", index_html);
}

void handleStatus(AsyncWebServerRequest *request) {
  String s1 = (digitalRead(ledPin1) ? "ON" : "OFF");
  String s2 = (digitalRead(ledPin2) ? "ON" : "OFF");
  String s3 = (digitalRead(ledPin3) ? "ON" : "OFF");
  String s4 = (digitalRead(fanPin1) ? "ON" : "OFF");
  String s5 = (digitalRead(fanPin2) ? "ON" : "OFF");
  
  String status = "{\"led1\":\"" + s1 + "\",\"led2\":\"" + s2 +"\",\"led3\":\"" + s3 +"\",\"fan1\":\"" + s4 +"\",\"fan2\":\"" + s5 + "\"}";
  request->send(200, "application/json", status);
}

void handleLed1(AsyncWebServerRequest *request) {

  String state = "0";
  if (request->hasParam("state1")) {
      state = request->getParam("state1")->value();

      if(state == "1") {
        digitalWrite(ledPin1, HIGH);
      }
      else {
        digitalWrite(ledPin1, LOW);
      }

      ledState1 = !ledState1;
  }
  Serial.println(state);
  request->send(200, "text/plain", state);
}

void handleLed2(AsyncWebServerRequest *request) {

  String state = "0";
  if (request->hasParam("state2")) {
      state = request->getParam("state2")->value();
      if(state == "1") {
        digitalWrite(ledPin2, HIGH);
      }
      else {
        digitalWrite(ledPin2, LOW);
      }
      // digitalWrite(ledPin2, state.toInt());
      ledState2 = !ledState2;
  }
  Serial.println(state);
  request->send(200, "text/plain", state);

}

void handleLed3(AsyncWebServerRequest *request) {
  String state = "0";
  if (request->hasParam("state3")) {
      state = request->getParam("state3")->value();
      if(state == "1") {
        digitalWrite(ledPin3, HIGH);
      }
      else {
        digitalWrite(ledPin3, LOW);
      }

      ledState3 = !ledState3;
  }
  Serial.println(state);
  request->send(200, "text/plain", state);
}

void handleFan1(AsyncWebServerRequest *request) {
  String state = "0";
  if (request->hasParam("state1")) {
      state = request->getParam("state1")->value();
      if(state == "1") {
        digitalWrite(fanPin1, HIGH);
      }
      else {
        digitalWrite(fanPin1, LOW);
      }

      fanState1= !fanState1;
  }
  Serial.println(state);
  request->send(200, "text/plain", state);
}
void handleFan2(AsyncWebServerRequest *request) {
  String state = "0";
  if (request->hasParam("state2")) {
      state = request->getParam("state2")->value();
      if(state == "1") {
        digitalWrite(fanPin2, HIGH);
      }
      else {
        digitalWrite(fanPin2, LOW);
      }

      fanState2 = !fanState2;
  }
  Serial.println(state);
  request->send(200, "text/plain", state);
}

void handleUltraSonic(AsyncWebServerRequest *request) {
  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58;
  
  request->send(200, "text/plain", String(distance));
}

void handleDht11(AsyncWebServerRequest *request) {
  humi = dht.readHumidity();
  temp = dht.readTemperature();

  String status = "{\"temp\":\"" + String(temp) + "\",\"humi\":\"" + String(humi) +"\"}";
  request->send(200, "application/json", status);
}


  