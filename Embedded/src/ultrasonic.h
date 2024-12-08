#ifndef ultrasonic_h
#define ultrasonic_h
#define TRIG_PIN 21
#define ECHO_PIN 20
#include <stdbool.h>
#include <stdint.h>
#include "pico/stdlib.h"
void setupUltrasonicPins();
uint64_t getCm();
uint64_t getInch();
#endif