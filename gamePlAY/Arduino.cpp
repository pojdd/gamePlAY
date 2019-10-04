#include "Arduino.h"



Arduino::Arduino()
{
}


Arduino::~Arduino()
{
	delete arduino;
}
bool Arduino::init()
{
	return seachPort();
}
char Arduino::sendmsg(char data)
{
	if (arduino == NULL) {
		printf("null\n");
		seachPort();
		return -1;
	}
	if (!arduino->isConnected()) {
		printf("未连接\n");
		seachPort();
		return -1;
	}
	Sleep(1);
	arduino->writeSerialPort(&data, 1);
	return data;
}
char Arduino::sendmsg(signed char data)
{
	if (arduino == NULL) {
		printf("null\n");
		seachPort();
		return -1;
	}
	if (!arduino->isConnected()) {
		delete arduino;
		seachPort();
		return -1;
	}
	Sleep(5);
	arduino->writeSerialPort((char*)&data, 1);
	return data;
}
char Arduino::getmsg()
{
	Sleep(5);
	signed char data;
	arduino->readSerialPort((char*)&data, 1);
	return data;
}
bool Arduino::seachPort()
{
	/*
	char portName[] = "\\\\.\\COM20";
	char CurrPortName[100];
	for (int a = 1; a < 30;a++)
	{
		sprintf_s(CurrPortName,"\\\\.\\COM%d",a);
		printf("%s\n", CurrPortName);
		arduino = new SerialPort(CurrPortName);
		if (arduino->isConnected()) {
			char data[DATA_LENGTH];
			data[0] = 0x15;
			cout<<arduino->writeSerialPort(data,1)<<endl;
			int hasRead = arduino->readSerialPort(data, 1);
			if (hasRead)
			{
				printf("%X", data[0]);
				return true;
			}
			else
				printf("Error occured reading data");

		}
		delete arduino;


	}
	return false;
	*/
	CRegKey RegKey;
	int nCount = 0;
	char list[100][100];
	if (RegKey.Open(HKEY_LOCAL_MACHINE, L"HARDWARE\\DEVICEMAP\\SERIALCOMM") == ERROR_SUCCESS)
	{
		while (true)
		{
			WCHAR ValueName[100];
			//char ValueName[_MAX_PATH];
			unsigned char ValueData[_MAX_PATH];
			DWORD nValueSize = _MAX_PATH;
			DWORD nDataSize = _MAX_PATH;
			DWORD nType;
			if (::RegEnumValue(HKEY(RegKey), nCount, ValueName, &nValueSize, NULL, &nType, ValueData, &nDataSize) == ERROR_NO_MORE_ITEMS)
			{
				break;
			}
			const WCHAR *str = L"\\Device\\USBSER000";
			if (!StrCmpCW(str, ValueName)) {
				//wcout << (WCHAR *)ValueData << endl;
				//wcout << ValueName << endl;
				char comn[10] = "";
				for (int a = 0; ValueData[a] != 0; a += 2) {
					comn[a / 2] = ValueData[a];
				}
				char CurrPortName[100];
				sprintf_s(CurrPortName, "\\\\.\\%s", comn);

				arduino = new SerialPort(CurrPortName);
				if (arduino->isConnected()) {
					char data;
					data = 0x15;
					arduino->writeSerialPort(&data, 1);
					Sleep(10);
					int hasRead = arduino->readSerialPort(&data, 1);
					if (hasRead)
					{
						//printf("%X", data[0]);
						if (data == 0x71) {
							printf("已连接\n");
							return true;
						}
						return false;
					}
				}
				delete arduino;
			}
			nCount++;
		}
		return false;
	}
	return 0;
}