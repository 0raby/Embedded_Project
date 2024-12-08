#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "waterLevel.h"
#include "hardware/adc.h"

void c43_init() {
    // Initialize ADC for the sensor
    adc_init();
    adc_gpio_init(WATERLVL_SENSOR_PIN);
    adc_select_input(0); // Use ADC channel 0
}

float c43_read_level() {
    // Read raw ADC value
    uint16_t raw = adc_read();
    // Convert to voltage (3.3V reference, 12-bit ADC)
    float voltage = raw * (3.3f / (1 << 12));
    // // Map voltage to water level (assuming 0-100% scale)
    float level=((voltage / 3.3f) * 100.0f);
    // level = level *1.2f;
    // level-=4.34?512;
    if(level <=45.0f){
        level-=30.43932f;
    }
    if(level>= 55.0f){
        level+=28.23451;
    }
    if(level<0.0f) {
        level=0.01292f;
    }
    if(level>= 100){
        level=98.70237;
    }
    
    return level;
}