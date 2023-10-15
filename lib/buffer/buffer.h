#ifndef BUFFER_H
#define BUFFER_H
#include <stdint.h>



class Buffer
{
public:
	enum class status
	{	
		ok,
		bufferEmpty,
		bufferFull
		
	};

private:
	static const int bSize=256;
	volatile uint8_t  head=0;
	volatile uint8_t tail=0;


public:
	char buffer [bSize];
	bool empty();
	void flush();
	status write(char _data);
	status read(char* _data);
};





#endif // BUFFER_H