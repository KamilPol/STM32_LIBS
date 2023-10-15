#include "hd44780.h"

HD44780::HD44780(I2C* _i2c, uint8_t _address) : address (_address), i2c( _i2c)
{
	LCDdata = 0x0;
}
void HD44780::Init()
{	
	LCDdata = 0x0; 
	lcd.backLight(true);
	lcd.sendHalfByte(0x03, modes::command);
	delay(5);
	lcd.sendHalfByte(0x03, modes::command);
	delay(5);
	lcd.sendHalfByte(0x03, modes::command);
	delay(5);
	lcd.sendHalfByte(0x02, modes::command);
	delay(5);
	lcd.sendByte(0x28, modes::command); // 4 bit, 2 lines, 5x8
	delay(5);
	lcd.sendByte(0xC, modes::command); // display on, cursor off, blinking cursor off
	delay(5);
	lcd.sendByte(0x01, modes::command); // clear display
	delay(5);
	lcd.sendByte(0x06, modes::command); // entry mode, set increment
}
void HD44780::sendHalfByte(uint8_t _data, modes _mode) 
{   
	LCDdata &= ~0xF0;
	LCDdata |= _data<<4;
	LCDdata |= EN; 
	LCDdata &= ~RW; 
	_mode == modes::data ? LCDdata |= RS : LCDdata &= ~RS; 
	i2c->sendByte(&LCDdata, address);
	LCDdata &= ~EN; 
	i2c->sendByte(&LCDdata, address);
}
void HD44780::sendByte(uint8_t _data, modes _mode) 
{
	sendHalfByte(_data>>4, _mode);
	sendHalfByte(_data, _mode);
}
void HD44780::backLight(bool _state)
{
	_state ? LCDdata |= BL : LCDdata &= ~BL;
	i2c->sendByte(&LCDdata, address);
}
void HD44780::sendChar(char _char)
{
	sendByte(_char, modes::data);
}
void HD44780::print(const char* _string)
{
	while (*_string)
	{
		sendChar(*_string++);
	}
}
void HD44780::clear()
{
	sendByte(0x1, modes::command);
	//delay(5);
}
void HD44780::returnHome()
{
	sendByte(0x2, modes::command);
	//delay(5);
}
uint8_t HD44780::checkBF() // sprawdzić odbieranie na I2C
{
	uint8_t checkFlag =0b10000000; // 1 on MSB is needed to set expander P7 in read mode
	checkFlag |= RW;

	i2c->sendByte(&checkFlag, address);
	checkFlag |= EN ;

	i2c->sendByte(&checkFlag, address);
	
	
	uint8_t tmpRcvByte = i2c->recieveByte(address);
	checkFlag &= ~EN;
	i2c->sendByte(&checkFlag, address);
	return tmpRcvByte;
}

