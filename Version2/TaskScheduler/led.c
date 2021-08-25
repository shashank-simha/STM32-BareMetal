/*
 * led.c
 *
 *  Created on: 25-Aug-2021
 *      Author: simha
 */

#include<stdint.h>
#include "led.h"

void delay(uint32_t count)
{
  for(uint32_t i = 0; i < count; i++);
}

void led_init_all(void)
{
	uint32_t *pRCCAHB1ENR 	= (uint32_t*) 0x40023830;
	uint32_t *pGPIOC_MODER 	= (uint32_t*) 0x40020800;
	uint32_t *pGPIOC_OTYPER = (uint32_t*) 0x40020804;

	// Enable GPIOC in AHB1ENR
	*pRCCAHB1ENR |= (0x01 << 2);

	// Set IO Direction Mode = Output(1)
	*pGPIOC_MODER &= ~(0x03 << (2 * LED_RED));
	*pGPIOC_MODER |=  (0x01 << (2 * LED_RED));
	*pGPIOC_MODER &= ~(0x03 << (2 * LED_GREEN));
	*pGPIOC_MODER |=  (0x01 << (2 * LED_GREEN));
	*pGPIOC_MODER &= ~(0x03 << (2 * LED_BLUE));
	*pGPIOC_MODER |=  (0x01 << (2 * LED_BLUE));
	*pGPIOC_MODER &= ~(0x03 << (2 * LED_WHITE));
	*pGPIOC_MODER |=  (0x01 << (2 * LED_WHITE));

	// Set IO Output Type = Push-Pull Output (0)
	*pGPIOC_OTYPER &= ~(0x01 << LED_RED);
	*pGPIOC_OTYPER |=  (0x00 << LED_RED);
	*pGPIOC_OTYPER &= ~(0x01 << LED_GREEN);
	*pGPIOC_OTYPER |=  (0x00 << LED_GREEN);
	*pGPIOC_OTYPER &= ~(0x01 << LED_BLUE);
	*pGPIOC_OTYPER |=  (0x00 << LED_BLUE);
	*pGPIOC_OTYPER &= ~(0x01 << LED_WHITE);
	*pGPIOC_OTYPER |=  (0x00 << LED_WHITE);

    led_on(LED_RED);
    led_on(LED_GREEN);
    led_on(LED_BLUE);
    led_on(LED_WHITE);
}

void led_on(uint8_t led_no)
{
  uint32_t *pGPIOC_ODR = (uint32_t*)0x40020814;
  *pGPIOC_ODR |= (0x1 << led_no);
}

void led_off(uint8_t led_no)
{
	uint32_t *pGPIOC_ODR = (uint32_t*)0x40020814;
	*pGPIOC_ODR &= ~(0x1 << led_no);
}
