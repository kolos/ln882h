#include <ln882h-hal-gpio.h>
#include "hal/hal_common.h"
#include "hal/hal_gpio.h"
#include "hal/hal_ext.h"

typedef struct {
    uint32_t base;
    gpio_pin_t pin;

    uint8_t irq_enabled;
    void (*irq_handler)(void);
} gpio_t;

static gpio_t gpio_pins[] = {
    { .base = GPIOA_BASE, .pin = GPIO_PIN_0 },  // PIN_A0
    { .base = GPIOA_BASE, .pin = GPIO_PIN_1 },  // PIN_A1
    { .base = GPIOA_BASE, .pin = GPIO_PIN_2 },  // PIN_A2
    { .base = GPIOA_BASE, .pin = GPIO_PIN_3 },  // PIN_A3
    { .base = GPIOA_BASE, .pin = GPIO_PIN_4 },  // PIN_A4
    { .base = GPIOA_BASE, .pin = GPIO_PIN_5 },  // PIN_A5
    { .base = GPIOA_BASE, .pin = GPIO_PIN_6 },  // PIN_A6
    { .base = GPIOA_BASE, .pin = GPIO_PIN_7 },  // PIN_A7
    { .base = GPIOA_BASE, .pin = GPIO_PIN_8 },  // PIN_A8
    { .base = GPIOA_BASE, .pin = GPIO_PIN_9 },  // PIN_A9
    { .base = GPIOA_BASE, .pin = GPIO_PIN_10 }, // PIN_A10
    { .base = GPIOA_BASE, .pin = GPIO_PIN_11 }, // PIN_A11
    { .base = GPIOA_BASE, .pin = GPIO_PIN_12 }, // PIN_A12
    { .base = GPIOA_BASE, .pin = GPIO_PIN_13 }, // PIN_A13
    { .base = GPIOA_BASE, .pin = GPIO_PIN_14 }, // PIN_A14
    { .base = GPIOA_BASE, .pin = GPIO_PIN_15 }, // PIN_A15

    { .base = GPIOB_BASE, .pin = GPIO_PIN_0 },  // PIN_B0
    { .base = GPIOB_BASE, .pin = GPIO_PIN_1 },  // PIN_B1
    { .base = GPIOB_BASE, .pin = GPIO_PIN_2 },  // PIN_B2
    { .base = GPIOB_BASE, .pin = GPIO_PIN_3 },  // PIN_B3
    { .base = GPIOB_BASE, .pin = GPIO_PIN_4 },  // PIN_B4
    { .base = GPIOB_BASE, .pin = GPIO_PIN_5 },  // PIN_B5
    { .base = GPIOB_BASE, .pin = GPIO_PIN_6 },  // PIN_B6
    { .base = GPIOB_BASE, .pin = GPIO_PIN_7 },  // PIN_B7
    { .base = GPIOB_BASE, .pin = GPIO_PIN_8 },  // PIN_B8
    { .base = GPIOB_BASE, .pin = GPIO_PIN_9 },  // PIN_B9
    { .base = GPIOB_BASE, .pin = GPIO_PIN_10 }, // PIN_B10
    { .base = GPIOB_BASE, .pin = GPIO_PIN_11 }, // PIN_B11
    { .base = GPIOB_BASE, .pin = GPIO_PIN_12 }, // PIN_B12
    { .base = GPIOB_BASE, .pin = GPIO_PIN_13 }, // PIN_B13
    { .base = GPIOB_BASE, .pin = GPIO_PIN_14 }, // PIN_B14
    { .base = GPIOB_BASE, .pin = GPIO_PIN_15 }  // PIN_B15
};

static const uint8_t gpio_pins_count = sizeof(gpio_pins) / sizeof(gpio_t);

static gpio_int_type_t modeToInterrupt(uint8_t interrupt_mode)
{
    if(interrupt_mode & RISING) {
        return GPIO_INT_RISING;
    }
    
    if(interrupt_mode & FALLING) {
        return GPIO_INT_FALLING;
    }
    
    if(interrupt_mode & CHANGE) {
        return GPIO_INT_RISING_FALLING;
    }

    return GPIO_INT_RISING;
}

static gpio_direction_t modeToDirection(uint8_t input_mode)
{
    if(input_mode & INPUT || input_mode & INPUT_PULLUP || input_mode & INPUT_PULLDOWN) {
        return GPIO_INPUT;
    }

    return GPIO_OUTPUT;
}

static gpio_pull_t modeToPull(uint8_t interrupt_mode)
{
    if(interrupt_mode & FALLING) {
        return GPIO_PULL_UP;
    }

    if(interrupt_mode & RISING ) {
        return GPIO_PULL_DOWN;
    }

    if(interrupt_mode & CHANGE) {
        return GPIO_PULL_UP_AND_PULL_DOWN;
    }

    return GPIO_PULL_NONE;
}

static IRQn_Type pinToIrq(uint8_t pin_number)
{
    return gpio_pins[pin_number].base == GPIOA_BASE ? GPIOA_IRQn : GPIOB_IRQn;
}



void pinMode(uint8_t pin_number, uint8_t input_mode)
{
    gpio_t *gpio = &gpio_pins[pin_number];

    gpio_init_t_def gpio_init = {
        .dir   = modeToDirection(input_mode),
        .pin   = gpio->pin,
        .speed = GPIO_HIGH_SPEED,
        .mode  = GPIO_MODE_DIGITAL,
        .pull  = GPIO_PULL_UP,
    };

    hal_gpio_init(gpio->base, &gpio_init);
}

void digitalWrite(uint8_t pin_number, uint8_t val)
{
    gpio_t *gpio = &gpio_pins[pin_number];

    if(val == 1) {
        hal_gpio_pin_set(gpio->base, gpio->pin);
    } else {
        hal_gpio_pin_reset(gpio->base, gpio->pin);
    }
}

int digitalRead(uint8_t pin_number)
{
    gpio_t *gpio = &gpio_pins[pin_number];

    return hal_gpio_pin_input_read(gpio->base, gpio->pin);
}

void attachInterrupt(uint8_t pin_number, void (*callback)(void), int interrupt_mode)
{
    gpio_t *gpio = &gpio_pins[pin_number];

    pinMode(pin_number, INPUT);
    hal_gpio_pin_it_cfg(gpio->base, gpio->pin, modeToInterrupt(interrupt_mode));
    hal_gpio_pin_it_en(gpio->base, gpio->pin, HAL_ENABLE);

    NVIC_SetPriority(pinToIrq(pin_number), 1);
    NVIC_EnableIRQ(pinToIrq(pin_number));

    gpio_pins[pin_number].irq_enabled = 1;
    gpio_pins[pin_number].irq_handler = callback;
}

void GPIO_IRQHandler()
{
    for(uint8_t i = 0; i < gpio_pins_count; i++) {
        gpio_t *gpio = &gpio_pins[i];

        if(gpio->irq_enabled == 0 || gpio->irq_handler == NULL) {
            continue;
        }

        if(hal_gpio_pin_get_it_flag(gpio->base, gpio->pin) == HAL_SET) {
            hal_gpio_pin_clr_it_flag(gpio->base, gpio->pin);
            
            gpio->irq_handler();
        }
    }
}

void GPIOB_IRQHandler()
{
    GPIO_IRQHandler();
}

void GPIOA_IRQHandler()
{
    GPIO_IRQHandler();
}