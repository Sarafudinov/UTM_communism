#include "Structures.h"

#define bLed 3
#define gLed 4
#define rLed 5

#define btn 2

Green g;
Blue b;
Red r;

LedState Normal[4] = {
  {0, 500, { r.OFF, g.ON,  b.OFF  }, 1 },
  {1, 300, { r.OFF, g.OFF, b.ON   }, 2 },
  {2, 500, { r.ON,  g.OFF, b.OFF  }, 3 },
  {3, 300, { r.OFF, g.OFF, b.ON   }, 0 }
};

LedState ForHumans[2] = {
  {0, 50, { r.OFF,  g.ON,   b.ON }, 1 },
  {1, 50, { r.ON,   g.OFF,  b.ON }, 0 },
};

Semafore FSM[2] = {
  {0, Normal, 1},
  {1, ForHumans, 0}
};

unsigned long timing;
int typeState = 0;
int fsmState = 0;


void setup() {

  Serial.begin(9600);
  
  pinMode(rLed, OUTPUT);
  pinMode(gLed, OUTPUT);
  pinMode(bLed, OUTPUT);
  
  pinMode(btn, INPUT_PULLUP);

}

void loop() {

 smType(FSM[fsmState].type);

if(!digitalRead(btn))
  if((millis() - timing > 300)){
    timing = millis();
    fsmState = FSM[fsmState].nextState;
  }	
}

void smType(LedState type[]) {

  rgb(  type[typeState].Color[0], 
        type[typeState].Color[1], 
        type[typeState].Color[2]
      );

  delay(type[typeState].Time * 10);

  typeState = type[typeState].nextState;
}

void rgb(int r, int g, int b) {
  
  digitalWrite(rLed, r);
  digitalWrite(gLed, g);
  digitalWrite(bLed, b);
}

