#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "fan.h"


// Function to set up PWM for the enable pin
void setup_pwm(uint pin, uint16_t duty_cycle) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_wrap(slice_num, 65535); // 16-bit resolution
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(pin), duty_cycle);
    pwm_set_enabled(slice_num, true);
}
void Init_Fan(){
    gpio_init(IN1_PIN);
    gpio_set_dir(IN1_PIN, GPIO_OUT);
    gpio_init(IN2_PIN);
    gpio_set_dir(IN2_PIN, GPIO_OUT);

    // Initial state
    set_direction(true); // Set fan to spin forward
    setup_pwm(EN_PIN, 32768); // 50% duty cycle for medium speed
}
// Function to set the fan direction
void set_direction(bool forward) {
    if (forward) {
        gpio_put(IN1_PIN, 1);
        gpio_put(IN2_PIN, 0);
    } else {
        gpio_put(IN1_PIN, 0);
        gpio_put(IN2_PIN, 1);
    }
}
