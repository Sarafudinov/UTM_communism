unsigned long timing = 0;
unsigned long timeTask1 = 0;
unsigned long timeTask2 = 0;
unsigned long timeTask3 = 0;
int interval = 100;
int time = 0;

int ledPinOnOff = 13;
int ledPinBlink = 12;

int onOffButton = 3;
int DecButton = 5;
int IncButton = 4;

void setup()
{
  pinMode(ledPinOnOff, OUTPUT);
  pinMode(ledPinBlink, OUTPUT);
  
  pinMode(onOffButton, INPUT_PULLUP);
  pinMode(DecButton, INPUT_PULLUP);
  pinMode(IncButton, INPUT_PULLUP);
  
  Serial.begin(9600);
  
}

void loop()
{  
  time = millis();
  int ms = 1000;

  firstTask(ms/2);

  secondTask(ms);
  
  threethTask(ms/5);
  
  
  Serial. print(millis());
  Serial. println(" millis() ");
  
}


void firstTask(int ms){
  Serial. print(" First TASK ");
  Serial. print(ms);
  Serial. print(" ms ");
  Serial. print(timeTask1);
  Serial. println(" time ");
  
  while(true){
    if(millis() - timeTask1 >= ms){
      timeTask1 = millis();
      timeTask2 = millis();
      timeTask3 = millis();
      return;
    }

    bool pushed = !digitalRead(onOffButton);

    if(pushed && !digitalRead(ledPinOnOff)){
      ledOnOff(true, "led on");
    }

    if(pushed && digitalRead(ledPinOnOff)){
      ledOnOff(false, "led off");
    }
  }
    
}

void ledOnOff(bool state, String message){
  if((millis() - timing > 300)){
    Serial.println(message);
    timing = millis();
    digitalWrite(ledPinOnOff, state);
  }	
}

void secondTask(int ms){
  Serial. print(" Second TASK ");
  Serial. print(ms);
  Serial. print(" ms ");
  Serial. print(timeTask2);
  Serial. println(" time ");
  
  unsigned long previousMillis = 0;
  int ledState = LOW;

  while(!digitalRead(ledPinOnOff)){
    if(millis() - timeTask2 >= ms){
      timeTask1 = millis();
      timeTask2 = millis();
      timeTask3 = millis();
      return;
    }
    
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      digitalWrite(ledPinBlink, ledState);
    }
  }
  digitalWrite(ledPinBlink, LOW);
}

void threethTask(int ms){
  Serial. print(" Threeth TASK ");
  Serial. print(ms);
  Serial. print(" ms ");
  Serial. print(timeTask3);
  Serial. println(" time ");
  
  unsigned long previousMillis = 0;
  while(true){
    if(millis() - timeTask3 >= ms){
      timeTask1 = millis();
      timeTask2 = millis();
      timeTask3 = millis();
      return;
    }

    bool pushDec = !digitalRead(DecButton);
    bool pushInc = !digitalRead(IncButton);

    unsigned long currentMillis = millis();
	int delay = 500;
    int val = 100;
    
    if(pushDec){
      if (currentMillis - previousMillis >= delay) {
        previousMillis = currentMillis;
        if (interval > 0) interval -= val;
        Serial.println(" decr ");     
      }
    }
    if(pushInc){
      if (currentMillis - previousMillis >= delay) {
        previousMillis = currentMillis;
        interval+=val;
        Serial.println(" incr "); 
      }
    }
  }
}




