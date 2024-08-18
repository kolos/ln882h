// SPDX-License-Identifier: LGPL-2.1-only
// Copyright (C) 2020 Marek Kraus <gamelaster@outlook.com>

#include "Arduino.h"

void yield()
{
    portYIELD();
}

unsigned long millis(void)
{
    return xTaskGetTickCount() * portTICK_PERIOD_MS;
}

void delay(uint32_t ms)
{
    vTaskDelay(ms / portTICK_PERIOD_MS);
}

void arduinoTask(void *params)
{
  setup();
  while (1) {
    loop();
    vTaskDelay(1);
    taskYIELD();
  }
}

extern "C" void arduino_main()
{
  xTaskCreate(arduinoTask, (char*)"arduinoTask", 4096, NULL, 10, NULL);
  //arduinoTask(NULL);
}