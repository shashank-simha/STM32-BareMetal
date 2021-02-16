#include "NVIC.h"

void EXTI15_10_IRQHandler(void)
{
    // Make sure that the 15:10 is triggered
    if (EXTI->PR & (1 << B1_Pin))
    {
        // clear the interrupt
        EXTI->PR |= (1 << B1_Pin);

        // Toggle LED
        LED_Status = !LED_Status;
    }
}