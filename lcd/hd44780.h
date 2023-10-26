#ifndef HD44780_H
#define HD44780_H
#include "i2c.h"
#include "board.h"
class I2C;
#define QueqeLength 256
#define RS 0x01
#define RW 0x02
#define EN 0x04
#define BL 0x08
#define D4 0x10
#define D5 0x20
#define D6 0x40
#define D7 0x80
enum class LCDcomandType
{
	Print,
	Println,
	Clear,
	CarriageReturn
};
enum class modes
{
	command,
	data
};

class HD44780 
{
private:
	uint8_t LCDdata;
	void sendHalfByte(uint8_t _byte, modes _mode);
	void sendByte(uint8_t _byte, modes _mode);	
	uint8_t address;
	uint8_t characters;
	uint8_t lines;
	I2C* i2c;


public:
	HD44780(I2C* _i2c, uint8_t _address, uint8_t _characters, uint8_t _lines);
	void Init();
	void backLight(bool _state);
	void print(const char* _string);
	void sendChar(char _char);
	void clear();
	void returnHome();
	bool busy(); 
	void executeIfNotBusy(void (*_LCDfunction)());
	void setPosition (uint8_t _character, uint8_t line);

	
};





#endif // HD44780_H