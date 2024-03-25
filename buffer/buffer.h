#ifndef BUFFER_H
#define BUFFER_H
#include <stdint.h>


template < int bSize >

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
	//static const int bSize=256;
	volatile uint8_t  head=0;
	volatile uint8_t tail=0;


public:
	char buffer [bSize];
	bool empty()
	{
		if (tail==head) 
			return 1;
		return 0;		
	}
	void flush()
	{
		head=0;
		tail=0;
	}
	status write(char _data)
	{
	if ((head+1)==tail)
		return Buffer::status::bufferFull;
	
	buffer[head] = _data;
	head++;
	
	if ( head == (bSize-1) )
		head = 0;

	return Buffer::status::ok;
	
}
	status read(char* _data)
	{
	if (tail==head) 
		return Buffer::status::bufferEmpty;
		
	*_data=buffer[tail];
	tail++;

	if ( tail == (bSize-1) )
		tail = 0;

	return Buffer::status::ok;
}
};





#endif // BUFFER_H