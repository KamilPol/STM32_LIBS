#include "hd44780.h"

HD44780::HD44780(I2C* _i2c, uint8_t _address, uint8_t _characters, uint8_t _lines) : address (_address), i2c( _i2c), characters(_characters), lines(_lines)
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
bool HD44780::busy() 
{
	uint8_t checkFlag =0b10001000; // 1 on MSB is needed to set expander P7 in read mode, 1 on 4th bit for BL enable

	checkFlag |= RW;
	i2c->sendByte(&checkFlag, address);

	checkFlag |= EN ;
	i2c->sendByte(&checkFlag, address);
	
	
	uint8_t tmpRcvByte = i2c->recieveByte(address);
	checkFlag &= ~EN;
	i2c->sendByte(&checkFlag, address);

	if ((tmpRcvByte & 0b10000000))
		return true;
	return false;
}
void HD44780::executeIfNotBusy(void (*_LCDfunction)())
{
	if (!(busy()))
		_LCDfunction();
}

void HD44780::setPosition (uint8_t _character, uint8_t _line)
{
	uint8_t setPositionCommand = 0x80 + _character;
	if (_line > 0) setPositionCommand += 64;
	lcd.sendByte(setPositionCommand,modes::command);
}
