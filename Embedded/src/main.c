#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "fan.h"
#include "ultrasonic.h"
#include "DS18B20.h"
#include "waterLevel.h"
#include "pump.h"
#include "buzzer.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
// #include "semphr.h"

#define DS18B20_PIN 15 //water temp pin
bool Emergency1 = false ;
bool Emergency2 = false ;
bool Emergency3 = false ;

void ultra_and_buzzer(void * pvParameters){
    init_buzzer();
    setupUltrasonicPins();
    while(true){
        float distance = getCm();
        if(distance<= 10){
            Emergency1=true;
            Emergency2=true;
            Emergency3=true;
            printf("EMERGENCYYYY \n");
        }
        else{
            Emergency1=false;
            Emergency2=false;
            Emergency3=false;
        }
        if(Emergency1){
            buzzer_on();
        }
        else{
            buzzer_off();
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    
}

void waterLvl_and_pump(void * pvParameters){
    pump_init();
    c43_init();
    while(true){
        float waterLevel= c43_read_level();
        if(Emergency1){
            pump_off();
            printf("EMERGENCYYYY \n");
        }
        else{
            if(waterLevel<20){
                printf("LOW \n");
                pump_on();
            }
            if(waterLevel<70 && waterLevel>=20){
                printf("Medium \n");
                pump_on();
            }
            if(waterLevel>=70){
                printf("HIGH \n");
                pump_off();
            }
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    
}

void temp_and_fan(void * pvParameters){
    uint gpio_pin = DS18B20_PIN;
    ds18b20_init(gpio_pin);
    Init_Fan();
    float temp =0.0f;
    set_direction(true);
    while(true){
    ds18b20_read_temp(gpio_pin, &temp);
    
        if(Emergency1){
            setup_pwm(EN_PIN, 0); 
            printf("EMERGENCYYYY \n");
        }
        else{
            
            if(temp <20){
                setup_pwm(EN_PIN, 0); 
                printf("No fan \n");
            }
            if(temp>=20 && temp <50){
                setup_pwm(EN_PIN, 27500);
                printf("Fan 50 \n");
            }
            if(temp>=50){
                setup_pwm(EN_PIN, 65535);
                printf("Fan 100 \n");
            }
        } 
        vTaskDelay(pdMS_TO_TICKS(100));  
    }
}

// #define aref_voltage 3.3 

int main() {
    stdio_init_all();
    //for testing
    xTaskCreate(ultra_and_buzzer, "ultra&buzzer", 1024, NULL, 1, NULL);
    xTaskCreate(waterLvl_and_pump, "Lvl&pump", 1024, NULL, 1, NULL);
    xTaskCreate(temp_and_fan, "temp&fan", 1024, NULL, 1, NULL);
    // xTaskCreate(led_task, "LED_Task", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    while(true){

    };
}