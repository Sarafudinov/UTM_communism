#include "termoSensor.h"
DHT dht(DHTPIN, DHTTYPE, 6);
unsigned long timing;

result TermoHumiditySensor(){
  dht.begin();

  float h, t, f, hi;
  char err [] ="nothing";
  while(millis() - timing <= 1000){}
  timing = millis(); 

  h = dht.readHumidity();
  t = dht.readTemperature();
  f = dht.readTemperature(true);
  
  if (isnan(h) || isnan(t) || isnan(f)) {
    for(char& c : err) {
      c='\0';
    }

    strcat(err, "Failed to read from DHT sensor!");
    return;
  }

  hi = dht.computeHeatIndex(f, h);
  return result {h, t, f, hi, err};

}




