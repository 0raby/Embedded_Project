#include "pico/stdlib.h"
#include "buzzer.h"

void init_buzzer(){
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
}
void buzzer_off(){
    gpio_put(BUZZER_PIN,0);
}
void buzzer_on(){
    gpio_put(BUZZER_PIN,1);

}