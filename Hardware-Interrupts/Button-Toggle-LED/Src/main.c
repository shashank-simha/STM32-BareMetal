/**
 * Main program.
 */

#include "main.h"

int main(void) 
{
  // Initialize global variables
  LED_Status = 0;

  // Enable SYSCFG peripheral
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

  // Enable GPIOPortA and GPIOPortC
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

  // Set Button Pin to Input mode with Pull-Up
  B1_GPIO_Port->MODER &= ~(0x03 << (B1_Pin*2));
  B1_GPIO_Port->MODER |=  (0x00 << (B1_Pin*2));
  B1_GPIO_Port->PUPDR &= ~(0x03 << (B1_Pin*2));
  B1_GPIO_Port->PUPDR |=  (0x01 << (B1_Pin*2));

  // Set LED Pin to Push-Pull Low-speed Output with no pull up
  LD2_GPIO_Port->MODER      &= ~(0x03 << (LD2_Pin*2));
  LD2_GPIO_Port->MODER      |=  (0x01 << (LD2_Pin*2));
  LD2_GPIO_Port->PUPDR      &= ~(0x03 << (LD2_Pin*2));
  LD2_GPIO_Port->PUPDR      |=  (0x00 << (LD2_Pin*2));
  LD2_GPIO_Port->OSPEEDR    &= ~(0x03 << (LD2_Pin*2));
  LD2_GPIO_Port->OSPEEDR    |=  (0x00 << (LD2_Pin*2));
  LD2_GPIO_Port->OTYPER     &= ~(0x01 << LD2_Pin);
  LD2_GPIO_Port->OTYPER     |=  (0x00 << LD2_Pin);

  // Configure SYSCFG to connect EXTI line to Button Pin (GPIOC, Pin 13)
  SYSCFG->EXTICR[(B1_Pin/4)] &= ~(0x0F << (B1_Pin % 4) * 4);
  SYSCFG->EXTICR[(B1_Pin/4)] |=  (0x02 << (B1_Pin % 4) * 4);

  // Set Button interrupt to unmasked
  EXTI->IMR |= (0x01 << B1_Pin);

  // Diasable Rising edge trigger
  EXTI->RTSR &= ~(0x01 << B1_Pin);

  // Enable Falling edge tringger
  EXTI->FTSR |=  (0x01 << B1_Pin);

  // Enable NVIC interrupt at minimum priority
  NVIC_SetPriority(EXTI15_10_IRQn, 0x00);
  NVIC_EnableIRQ(EXTI15_10_IRQn);

  // Set LED value based on status
  while (1)
  {
    if (LED_Status)
    {
      LD2_GPIO_Port->ODR |= (1 << LD2_Pin);
    }
    else
    {
      LD2_GPIO_Port->ODR &= ~(1 << LD2_Pin); 
    } 
  }
}