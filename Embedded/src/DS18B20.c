#include "pico/stdlib.h"
#include "DS18B20.h"

void ds18b20_init(uint gpio) {
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_OUT);
}

bool ds18b20_reset(uint gpio) {
    gpio_set_dir(gpio, GPIO_OUT);
    gpio_put(gpio, 0);
    sleep_us(480); // Reset pulse
    gpio_set_dir(gpio, GPIO_IN);
    sleep_us(70);  // Wait for presence pulse
    bool presence = gpio_get(gpio) == 0;
    sleep_us(410); // Complete timeslot
    return presence;
}

void ds18b20_write_bit(uint gpio, bool bit) {
    gpio_set_dir(gpio, GPIO_OUT);
    gpio_put(gpio, 0);
    sleep_us(bit ? 6 : 60);
    gpio_put(gpio, bit);
    gpio_set_dir(gpio, GPIO_IN);
    sleep_us(bit ? 64 : 10);
}

bool ds18b20_read_bit(uint gpio) {
    gpio_set_dir(gpio, GPIO_OUT);
    gpio_put(gpio, 0);
    sleep_us(6);
    gpio_set_dir(gpio, GPIO_IN);
    sleep_us(9);
    bool bit = gpio_get(gpio);
    sleep_us(55);
    return bit;
}

void ds18b20_write_byte(uint gpio, uint8_t data) {
    for (int i = 0; i < 8; i++) {
        ds18b20_write_bit(gpio, data & 0x01);
        data >>= 1;
    }
}

uint8_t ds18b20_read_byte(uint gpio) {
    uint8_t data = 0;
    for (int i = 0; i < 8; i++) {
        if (ds18b20_read_bit(gpio)) {
            data |= (1 << i);
        }
    }
    return data;
}

bool ds18b20_read_temp(uint gpio, float *temperature) {
    if (!ds18b20_reset(gpio)) {
        return false;
    }

    ds18b20_write_byte(gpio, 0xCC); // Skip ROM
    ds18b20_write_byte(gpio, 0x44); // Start temperature conversion

    sleep_ms(750); // Wait for conversion

    if (!ds18b20_reset(gpio)) {
        return false;
    }

    ds18b20_write_byte(gpio, 0xCC); // Skip ROM
    ds18b20_write_byte(gpio, 0xBE); // Read scratchpad

    uint8_t lsb = ds18b20_read_byte(gpio);
    uint8_t msb = ds18b20_read_byte(gpio);

    int16_t raw_temp = (msb << 8) | lsb;
    *temperature = raw_temp / 16.0;
    return true;
}
