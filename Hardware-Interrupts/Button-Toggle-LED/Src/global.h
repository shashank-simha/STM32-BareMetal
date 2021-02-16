#ifndef __GLOBAL_H
#define __GLOBAL_H

#include <stdint.h>
#include "stm32f446xx.h"

#define B1_Pin 13
#define B1_GPIO_Port GPIOC
#define LD2_Pin 5
#define LD2_GPIO_Port GPIOA

volatile uint8_t LED_Status;

#endif