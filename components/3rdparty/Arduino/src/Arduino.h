/*
 Arduino.h - Main include file for the Arduino SDK
 Copyright (c) 2005-2013 Arduino Team.  All right reserved.
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef Arduino_h
#define Arduino_h

#include <FreeRTOS.h>
#include <task.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <algorithm>
#include <cmath>

#ifdef __cplusplus
extern "C" {
#endif
	#include <log.h>
	extern TaskHandle_t rtosMainTask;
	#include "ln882h-hal-gpio.h"
#ifdef __cplusplus
}
#endif

#include "binary.h"

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define SERIAL  0x0
#define DISPLAY 0x1

#define LSBFIRST 0
#define MSBFIRST 1

#define digitalPinToPort(pin)       (pin % 32)
#define digitalPinToBitMask(pin)    (1UL << (pin % 32))
//#define digitalPinToTimer(pin)      (0)
//#define analogInPinToBit(P)         (P) // TODO: 
#define portOutputRegister(port)    ((volatile uint32_t*)(0x40000000 + 0x188 + (port * 4)))
#define portInputRegister(port)     ((volatile uint32_t*)(0x40000000 + 0x180 + (port * 4)))
//#define portModeRegister(port)      ((volatile uint32_t*)((port)?GPIO_ENABLE1_REG:GPIO_ENABLE_REG))

// Definitions for error constants.
#define esp_err_t int
#define ESP_OK	  0	 /*!< esp_err_t value indicating success (no error) */
#define ESP_FAIL  -1 /*!< Generic esp_err_t code indicating failure */

// ESP32 compat
//#define log_printf(...)		
#define log_v(...)			LOG(LOG_LVL_TRACE, __VA_ARGS__)
#define log_d(...)			LOG(LOG_LVL_DEBUG, __VA_ARGS__)
#define log_i(...)			LOG(LOG_LVL_INFO, __VA_ARGS__)
#define log_w(...)			LOG(LOG_LVL_WARN, __VA_ARGS__)
#define log_e(...)			LOG(LOG_LVL_ERROR, __VA_ARGS__)
#define log_n(...)			LOG(LOG_LVL_EMERG, __VA_ARGS__)
#define isr_log_v(...)		
#define isr_log_d(...)		
#define isr_log_i(...)		
#define isr_log_w(...)		
#define isr_log_e(...)		
#define isr_log_n(...)		
#define ESP_LOGV(...)		LOG(LOG_LVL_TRACE, __VA_ARGS__)
#define ESP_LOGD(...)		LOG(LOG_LVL_DEBUG, __VA_ARGS__)
#define ESP_LOGI(...)		LOG(LOG_LVL_INFO, __VA_ARGS__)
#define ESP_LOGW(...)		LOG(LOG_LVL_WARN, __VA_ARGS__)
#define ESP_LOGE(...)		LOG(LOG_LVL_ERROR, __VA_ARGS__)
#define ESP_EARLY_LOGV(...) 
#define ESP_EARLY_LOGD(...) 
#define ESP_EARLY_LOGI(...) 
#define ESP_EARLY_LOGW(...) 
#define ESP_EARLY_LOGE(...) 
#define ets_printf(...)		LOG(LOG_LVL_INFO, __VA_ARGS__)
#define ETS_PRINTF(...)		LOG(LOG_LVL_INFO, __VA_ARGS__)

// FreeRTOS utilities
#define xTaskCreateUniversal(pxTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask, xCoreID)       \
	xTaskCreate(pxTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask)
#define xTaskCreatePinnedToCore xTaskCreateUniversal

// Default values from sdkconfig.h
#define CONFIG_LWIP_MAX_ACTIVE_TCP 16

#define bit(b) (1UL << (b))
#define _BV(b) (1UL << (b))



typedef bool boolean;
typedef uint8_t byte;
typedef unsigned int word;

void yield(void);
unsigned long millis(void);
void delay(uint32_t ms);

void setup(void);
void loop(void);


#include "WString.h"
#include "Stream.h"
#include "Printable.h"
#include "Print.h"
#include "HardwareSerial.h"


#endif