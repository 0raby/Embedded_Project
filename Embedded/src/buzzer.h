#ifndef buzzer_h
#include "pico/stdlib.h"
#define buzzer_h
#define BUZZER_PIN 25
void init_buzzer();
void buzzer_off();
void buzzer_on();
#endif