#include <DHT.h>
#include <DHT_U.h>

#define DHT11PIN 5

DHT dht(DHT11PIN, DHT11);
float humi,temp;

void dht11Setup(){
  dht.begin();
}
