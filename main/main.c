/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const int LED_PIN = 5;
const int BUTTON_PIN = 7;
const int MOTOR_PINS[4] = {18, 19, 20, 21};
const int sequencia[8][4] = {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}
};

void motor_360() {
    for (int i = 0; i < 512; i++) {
        for (int passo = 0; passo < 8; passo++) {
            for (int pino = 0; pino < 4; pino++) {
                gpio_put(MOTOR_PINS[pino], sequencia[passo][pino]);
            }
            sleep_ms(2); 
        }
    }
    
    for (int pin = 0; pin < 4; pin++) gpio_put(MOTOR_PINS[pin], 0);
}

int main() {
    stdio_init_all();
    
    sleep_ms(2000);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
    
    for (int i = 0; i < 4; i++) {
        gpio_init(MOTOR_PINS[i]);
        gpio_set_dir(MOTOR_PINS[i], GPIO_OUT);
    }

    while (true) {
        if (!gpio_get(BUTTON_PIN)) {
            gpio_put(LED_PIN, 1);
            motor_360();
            sleep_ms(3500);
            gpio_put(LED_PIN, 0);
        }
        sleep_ms(10);
    }
}