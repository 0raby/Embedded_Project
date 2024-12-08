#ifndef DS18B20_H
#define DS18B20_H

#include <stdbool.h>
#include <stdint.h>
#include "pico/stdlib.h"

#define DS18B20_PIN 15

// Function declarations
void ds18b20_init(uint gpio);
bool ds18b20_reset(uint gpio);
void ds18b20_write_bit(uint gpio, bool bit);
bool ds18b20_read_bit(uint gpio);
void ds18b20_write_byte(uint gpio, uint8_t data);
uint8_t ds18b20_read_byte(uint gpio);
bool ds18b20_read_temp(uint gpio, float *temperature);

#endif 