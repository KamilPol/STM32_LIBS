#ifndef MOTOR_H 
#define MOTOR_H 

#include "stm32g4xx.h"




typedef enum
{
    FOC_MODE_OPEN_LOOP = 0,
    FOC_MODE_CLOSED_LOOP = 1
} FOCMode_TypeDef;

volatile float uQ1 = 0;
volatile float uD1 = 0;
volatile float iA1 = 0;
volatile float iB1 = 0;
volatile float iC1 = 0;
volatile float uAlpha1 = 0;
volatile float uBeta1 = 0;
volatile float iQ1 = 0;
volatile float iD1 = 0;
volatile float filterediQ1 = 0;
volatile float filterediD1 = 0;
volatile float angle1 = 0;


float setiQ1 = 0;
float setiD1 = 0;

void TIM1_UP_TIM16_IRQHandler(void);






#endif  // MOTOR_H