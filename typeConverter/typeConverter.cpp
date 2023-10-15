#include "typeConverter.h"


void typeConverter::IntToString (int _number, char * _string){
int i=0;
bool negative = _number<0? true : false;
int absNumber = _number<0? -_number : _number;
	if (absNumber==0) 
	{
		_string[0]='0';
		i=1;
	}
	while (absNumber)
	{
		_string[i++]=absNumber % 10 + '0';
		absNumber /= 10;
	}
	if (negative)
		_string[i++]='-';

	reverseArray(_string, i);
	_string[i]='\0';
}

void typeConverter::fractionalToString (double _number, char * _string, uint8_t _precision)
{
	int i=0;
	bool negative = _number<0? true : false;
	int64_t integerPart = static_cast<int64_t>(_number);
	double fractionalPart;
	fractionalPart =  _number - integerPart;
	fractionalPart <0 ? fractionalPart = -fractionalPart : fractionalPart = fractionalPart;
	int absNumber = integerPart < 0 ? -integerPart : integerPart;
	
	if (absNumber==0) 
	{
		_string[0]='0';
		i=1;
	}
	while (absNumber)
	{
		_string[i++]=absNumber % 10 + '0';
		absNumber /= 10;
	}
	if (negative)
		_string[i++]='-';
	reverseArray(_string, i);

	_string[i++]='.';

	for (int j=i; j<_precision+i; j++)
	{
		fractionalPart -= static_cast<int>(fractionalPart);
		fractionalPart *=10;
		_string[j]= static_cast<int>(fractionalPart) + '0';
	}
}


float typeConverter::stringToFloat(const char* _string)
{
    bool negative = false;
		int number = 0;
		if (*_string == '-')
			negative = true;
		while (*_string)
		{
			signed char c = *_string - '0';
			if (c>=0 && c<=9)
			{
				number = number * 10 + c;
			}
			_string ++;
		}
		if (negative)
			return -number;
		return number;
  
}
int typeConverter::stringToInt(const char* _string)
{
       	bool negative = false;
        bool isNumber = true;
		int number = 0;

		while (*_string && isNumber) 
		{
			int digit = *_string - '0';
        
			if (digit>=0 && digit<=9)			
				number = number * 10 + digit;
			else if (*_string == '-')
				negative = true;
			else
				isNumber = false;  

			_string ++;
		}

		if (negative)
			return -number;
		return number;
}

void typeConverter::reverseArray(char* _charTab, int _lenght)
{
	for (int i =0; i<_lenght/2; i++)
	{
		char temp = _charTab[i];
		_charTab [i] = _charTab [_lenght-i -1];
		_charTab [_lenght-i -1] = temp;
	}
}
        









