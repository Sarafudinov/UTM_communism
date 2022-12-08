
#include <Arduino.h>
#define LED_PIN 5
#define BTN_PIN 6

void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
}
static int btn_state = 1;
static int led_state = 0;

void loop()
{
  int check = digitalRead(BTN_PIN);
  if (!check && check != btn_state)
  {
    led_state = !led_state;
    digitalWrite(LED_PIN, led_state);
    int vol = analogRead(A0);
    if (vol > 300)
    {
      Serial.println("Lampa gorit!!!!!!!!!!!!!!!!!!!!!!");
    }
    else
    {
      Serial.println("Lampa ne gorit !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!?");
    }
  }
  btn_state = check;
}
