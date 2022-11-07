#include "termoSensor.h"
DHT dht(DHTPIN, DHTTYPE, 6);
unsigned long timing;

void setRGB(int R, int G, int B) {
  digitalWrite(pinRED,R);
  digitalWrite(pinGREEN,G);
  digitalWrite(pinBLUE,B);
}

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

  if (h < 40)
    setRGB(0,1,0);
  else if (h >= 40 && h < 60) 
    setRGB(0,0,1);
  else
    setRGB(1,0,0);

  return result {h, t, f, hi, err};

}




