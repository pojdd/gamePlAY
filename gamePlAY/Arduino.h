#pragma once
#include <Windows.h>
#include <conio.h>
#include "SerialPort.h"
#include "String.h"
#include <atlbase.h>
#define DATA_LENGTH 255
class Arduino
{
protected:
	
public:
	SerialPort * arduino;
	Arduino();  
	~Arduino();
	bool init();
	char sendmsg(char data);   
	char sendmsg(signed char data);
	char getmsg();
	bool seachPort();
};

