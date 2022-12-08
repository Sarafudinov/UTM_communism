#pragma once
#include "DHT.h"

#define DHTPIN A0
#define DHTTYPE DHT11  

struct result {float _h; float _t; float _f; float _hi; char *_err;};
result TermoHumiditySensor();

