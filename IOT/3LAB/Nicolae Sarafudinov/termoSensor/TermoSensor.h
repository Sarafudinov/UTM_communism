#pragma once
#include "DHT.h"

#define DHTPIN A0
#define DHTTYPE DHT11 

#define pinRED  5
#define pinGREEN  4
#define pinBLUE  3 

#define LEN  80 

struct result {float _h; float _t; float _f; float _hi; char *_err;};
result TermoHumiditySensor();

