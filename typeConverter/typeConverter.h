#ifndef typeConverter_H
#define typeConverter_H
#include <stdint.h>
#include <math.h>
class typeConverter
{


public:
    static void IntToString (int _number, char * _string);
    static void fractionalToString (float _number, char * _string, uint8_t _precision=3);
    static float stringToFloat(const char* _string);
    static int stringToInt(const char* _string);
    static void reverseArray(char* _charTab, int _lenght);
};



#endif // typeConverter_H