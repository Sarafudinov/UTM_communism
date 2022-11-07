#include "termoSensor.h"
#include "rangerSensor.h"
#include "filterSaltAndPapper.h"
#include "filterAverage.h"
#include "stdio.h"
#include "pins.h"
#include "MedianFilter.h"
#include <stdlib.h>
#include <unistd.h>


static FILE serial_stdinout = { .buf = NULL, .unget = 0, .flags = _FDEV_SETUP_RW, .size = 0, .len = 0, .put = serial_putchar, .get = serial_getchar, .udata = 0 };

#define NUM_ELEMENTS    7

static sMedianFilter_t medianFilter;
static sMedianNode_t medianBuffer[NUM_ELEMENTS];

void setup() {
  Serial.begin(9600);  

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);

  // Set up stdout and stdin
  stdout = &serial_stdinout;
  stdin  = &serial_stdinout;
  stderr = &serial_stdinout;
	
  medianFilter.numNodes = NUM_ELEMENTS;
  medianFilter.medianBuffer = medianBuffer;
    
  MEDIANFILTER_Init(&medianFilter);

}

void loop() {

  
  char msg[MSG_LEN] = {0};
  printf("\nEnter [b,f,t] ");

  scanf("%s",msg);
  printf("\n");
  
  if(strcmp(msg, "b") == 0){
    while(true){
      Serial.flush();
      beeeep();
    }
  }
  
  if(strcmp(msg, "f") == 0){
    while(true){
      Serial.flush();
      filtres();
    }
  }  
  
  if(strcmp(msg, "t") == 0){
    while(true){
      Serial.flush();
      TermoInfo();
    }
  } 

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


void filtres(){
// salt  and papper filter
  int window = 3;

  int distance[SIZE];
  int snpf[SIZE];
  int medf[SIZE];

  for(int k = 0; k < SIZE; k++){
    printf("\n\t\tdistnce: \n");   
    for(int i = 0; i < SIZE; i++){

      distance[i] = ranger(trigPin, echoPin);
      
      printArray(distance, SIZE, 3);
      snpf[i] = MEDIANFILTER_Insert(&medianFilter, distance[i]);
    }  
    printf("\n\tfiltered SnP:\n");
    printArray(snpf, SIZE, 2);
    medf[k] = smooth(snpf, SIZE, window);
  }

  printf("\nfiltered medf:\n");
  printArray(medf, SIZE, 1);
}

void printArray(int arr[], int size, int param)
{
  if (param == 1){
    for (int i = 0; i < size; i++)
        printf("%d \t", arr[i]);
  }
  if (param == 2){
    printf("\t");
    for (int i = 0; i < size; i++)
        printf("%d\t", arr[i]);
  }
  if (param == 3){
    printf("\t\t");
    for (int i = 0; i < size; i++)
        printf("%d\t", arr[i]);
  }

  printf("\n");
}


void beeeep(){
  if (ranger(trigPin, echoPin) <= 10)
  {
    tone(buzzer, 2000, 200);
  }
  else
  {
    noTone(buzzer);
  }
 }

