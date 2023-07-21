const char* ssid = "Galaxy M312D66";
const char* password = "aryanphone";

void wifiSetup(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}