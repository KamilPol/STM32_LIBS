#include "motor.h"


void TIM1_UP_TIM16_IRQHandler(void)
{
    TIM1->SR &= ~TIM_SR_UIF;
    static int i = 0;
    if (i < 10000)
    {
        i++;
    }
    else
    {
        i = 0;
        GPIOC->ODR ^= GPIO_ODR_OD4;
    }
    
    //PWMtim1ch1.toggle();
}
                                                                                                                                             
