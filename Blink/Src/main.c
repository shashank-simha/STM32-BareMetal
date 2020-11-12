/**
 * Main program.
 */

#include "main.h"

int main(void) 
{
  // Enable GPIOPortA and GPIOPortC
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  // RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

  // Set LED Pin to output
  LD2_GPIO_Port->MODER  &= ~(0x03 << (LD2_Pin*2));
  LD2_GPIO_Port->MODER  |=  (0x01 << (LD2_Pin*2));
  LD2_GPIO_Port->OTYPER &= ~(0x01 << LD2_Pin);

  LD2_GPIO_Port->ODR = 0xFF;

  while (1)
  {
    
  }

}