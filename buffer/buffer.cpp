#include "buffer.h"
//#include "UART.h"




    
Buffer::status Buffer::write(char _data)
{
	if ((head+1)==tail)
		return Buffer::status::bufferFull;
	
	buffer[head] = _data;
	head++;
	
	if ( head == (bSize-1) )
		head = 0;

	return Buffer::status::ok;
	
}

Buffer::status Buffer::read(char* _data)
{
	if (tail==head) 
		return Buffer::status::bufferEmpty;
		
	*_data=buffer[tail];
	tail++;

	if ( tail == (bSize-1) )
		tail = 0;

	return Buffer::status::ok;
}

bool Buffer::empty()
{
	if (tail==head) 
		return 1;
	return 0;		
}

void Buffer::flush()
{
	head=0;
	tail=0;
}