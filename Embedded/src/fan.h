#ifndef FAN_H
#define FAN_H
#include "pico/stdlib.h"
#define IN1_PIN 29  
#define IN2_PIN 28  
#define EN_PIN 12   
void setup_pwm(uint pin, uint16_t duty_cycle);
void Init_Fan();
void set_direction(bool forward);
#endif