#ifndef LN882H_HAL_GPIO_H
#define LN882H_HAL_GPIO_H

#include <stdint.h>

#define LOW               0x0
#define HIGH              0x1

//Pin Modes
#define INPUT             0x01
#define OUTPUT            0x02
#define PULLUP            0x04
#define INPUT_PULLUP      0x05
#define OUTPUT_PULLUP     0x06
#define PULLDOWN          0x08
#define INPUT_PULLDOWN    0x09
#define OUTPUT_PULLDOWN   0x0A
#define OPEN_DRAIN        0x10
#define OUTPUT_OPEN_DRAIN 0x12

//Interrupt Modes
#define RISING    0x01
#define FALLING   0x02
#define CHANGE    0x03
#define ONLOW     0x04
#define ONHIGH    0x05

#define PIN_A0 0
#define PIN_A1 1
#define PIN_A2 2
#define PIN_A3 3
#define PIN_A4 4
#define PIN_A5 5
#define PIN_A6 6
#define PIN_A7 7
#define PIN_A8 8
#define PIN_A9 9
#define PIN_A10 10
#define PIN_A11 11
#define PIN_A12 12
#define PIN_A13 13
#define PIN_A14 14
#define PIN_A15 15

#define PIN_B0 16
#define PIN_B1 17
#define PIN_B2 18
#define PIN_B3 19
#define PIN_B4 20
#define PIN_B5 21
#define PIN_B6 22
#define PIN_B7 23
#define PIN_B8 24
#define PIN_B9 25
#define PIN_B10 26
#define PIN_B11 27
#define PIN_B12 28
#define PIN_B13 29
#define PIN_B14 30
#define PIN_B15 31



void pinMode(uint8_t gpio_pin, uint8_t mode);
void digitalWrite(uint8_t gpio_pin, uint8_t val);
int digitalRead(uint8_t gpio_pin);
void attachInterrupt(uint8_t pin, void (*callback)(void), int mode);

#endif