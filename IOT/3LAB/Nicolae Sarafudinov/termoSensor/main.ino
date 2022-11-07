#include "termoSensor.h"
#include "stdio.h"

static FILE serial_stdinout = { .buf = NULL, .unget = 0, .flags = _FDEV_SETUP_RW, .size = 0, .len = 0, .put = serial_putchar, .get = serial_getchar, .udata = 0 };

void setup() {
  Serial.begin(9600);  

// Set up stdout and stdin
  stdout = &serial_stdinout;
  stdin  = &serial_stdinout;
  stderr = &serial_stdinout;
	
}

void loop() {
  TermoInfo();
}

void TermoInfo(){

  int i = 0;
  auto result = TermoHumiditySensor();
  
  printf("Humidity: %d %  \t ", (int)result._h ); 
  printf("Temperature: %d \ºC  %d \ºF\t", (int)result._t, (int)result._f);
  printf("Heat index: %d ºF\t ", (int)result._hi);
  printf("Error:");
  while(result._err[i] != '\0') {
    printf("%c", result._err[i++]);
  }
  printf("\n");
  i = 0;
}