/**
 * Main program.
 */

#include "main.h"

int main(void) 
{
  // Enable GPIOPortA and GPIOPortC
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

  // Set LED Pin to Low-speed Output 
  LD2_GPIO_Port->MODER  &= ~(0x03 << (LD2_Pin*2));
  LD2_GPIO_Port->MODER  |=  (0x01 << (LD2_Pin*2));
  LD2_GPIO_Port->OTYPER &= ~(0x01 << LD2_Pin);
  LD2_GPIO_Port->OTYPER |=  (0x00 << LD2_Pin);

  // Set Button Pin to Input mode with Pull-Up
  B1_GPIO_Port->MODER &= ~(0x03 << (B1_Pin*2));
  B1_GPIO_Port->MODER |=  (0x00 << (B1_Pin*2));
  B1_GPIO_Port->PUPDR &= ~(0x03 << (B1_Pin*2));
  B1_GPIO_Port->PUPDR |=  (0x01 << (B1_Pin*2));

  LD2_GPIO_Port->ODR |= (0x01 << LD2_Pin);

  // Keep track of whether the button is pressed.
  uint8_t button_down = 0;

  while (1)
  {
    // Invert the IDR register when button is pressed i.e; button_down = 0
    uint32_t idr_val = ~B1_GPIO_Port->IDR;
    if (idr_val & (1 << B1_Pin)) 
    {
      // The button is pressed; if it was not already pressed, change the LED state.
      if (!button_down) 
      {
        LD2_GPIO_Port->ODR ^= (1 << LD2_Pin);
      }
      button_down = 1;
    }
    else 
    {
      button_down = 0;
    }
  }

}