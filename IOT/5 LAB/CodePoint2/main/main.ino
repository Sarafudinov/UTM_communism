#include "stdio.h"
#include "termoSensor.h"

unsigned long time;

float termoStandard = 0;
int gestStep = 0;

int enB = 3;
int in3 = 5;
int in4 = 4;

int GL = 10;
int RL = 11;
int BL = 12;

int incB = 8;
int decB = 7;

static FILE serial_stdinout = { .buf = NULL, .unget = 0, .flags = _FDEV_SETUP_RW, .size = 0, .len = 0, .put = serial_putchar, .get = serial_getchar, .udata = 0 };

void setup() {
  Serial.begin(9600);

  // Set up stdout and stdin
  stdout = &serial_stdinout;
  stdin = &serial_stdinout;
  stderr = &serial_stdinout;

  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(GL, OUTPUT);
  pinMode(RL, OUTPUT);
  pinMode(BL, OUTPUT);
  
  pinMode(decB, INPUT_PULLUP);
  pinMode(incB, INPUT_PULLUP);

  // Turn off motors - Initial state
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

}

void loop() {

  BtnCheck();
  TermoInfo();
}

void TermoInfo() {

  // Termo sensor data
  auto result = TermoHumiditySensor();
  
  // init delay
  if(!initTermo(result._t)) { delay(100); }
  
  // work just after init
  if (initTermo(result._t) && gestStep) {
    float gestInc = termoStandard + gestStep;
    float gestDec = termoStandard - gestStep;
    float currTerm = result._t;

    // Serial.print(gestInc);
    // Serial.print(", ");
    // Serial.print(termoStandard);
    // Serial.print(", ");
    // Serial.print(gestDec);
    // Serial.print(", ");
    // Serial.println(currTerm);
    printf("%d,",  (int)gestInc);
    printf("%d,",  (int)termoStandard);
    printf("%d,",  (int)gestDec);
    printf("%d\n", (int)currTerm);

    if(currTerm == termoStandard) {
      RGB(0,0,1);
    }

    if(currTerm >= gestInc){
      motorStart();
    }

    if(currTerm <= gestDec){
      motorEnd();
    }
  }
  else
  {
    Serial.println("Push button ! ! !");
  }
}

bool initTermo(float term) {
  return termoStandard == 0 ? termoStandard = term +1 : termoStandard;
}

void motorStart() {
  //Serial.println("MOTOR ON");

  digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);

  RGB(0,1,0);

}

void motorEnd() {
  //Serial.println("MOTOR OFF");

  digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);

  RGB(1,0,0);

}

void RGB(int R, int G, int B) {
    digitalWrite(RL, R);
    digitalWrite(GL, G);
    digitalWrite(BL, B);
}

void BtnCheck() {
  int btnDelay = 100;

  if(!digitalRead(incB)) {
    if (millis() - time > btnDelay) { 
      time = millis(); 
      gestStep++;
    }
  }

  if(!digitalRead(decB)) {
    if (millis() - time > btnDelay) { 
      time = millis(); 
      if(gestStep > 1)
        gestStep--;
    }
  }
}