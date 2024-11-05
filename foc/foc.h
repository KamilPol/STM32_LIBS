#ifndef FOC.H
#define FOC.H

#include "stm32g4xx.h"
#include "board.h"

typedef enum
{
    FOC_MODE_OPEN_LOOP = 0,
    FOC_MODE_CLOSED_LOOP = 1
} FOCMode_TypeDef;

volatile float uQ = 0;
volatile float uD = 0;
volatile float iA = 0;
volatile float iB = 0;
volatile float iC = 0;
volatile float uAlpha = 0;
volatile float uBeta = 0;
volatile float iQ = 0;
volatile float iD = 0;
volatile float filterediQ = 0;
volatile float filterediD = 0;









#endif // FOC.H