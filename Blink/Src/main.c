/**
 * Main program.
 */

#include "main.h"

int main(void) 
{
  // Enable GPIOPortA and GPIOPortC
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  // Set LED Pin to Low-speed Output 
  LD2_GPIO_Port->MODER  &= ~(0x03 << (LD2_Pin*2));
  LD2_GPIO_Port->MODER  |=  (0x01 << (LD2_Pin*2));
  LD2_GPIO_Port->OTYPER &= ~(0x01 << LD2_Pin);
  LD2_GPIO_Port->OTYPER |=  (0x00 << LD2_Pin);

  LD2_GPIO_Port->ODR |= (0x01 << LD2_Pin);

  uint32_t i;

  while (1)
  {
    for (i = 0; i < 640000; i++);
    
    LD2_GPIO_Port->ODR ^= (1 << LD2_Pin);
  }
}