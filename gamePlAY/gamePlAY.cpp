#include <iostream>
#include <Windows.h>
#include "Arduino.h"
#define DATA_LENGTH 255
using namespace std;
POINT point;
RECT rect;


void getPoint()
{
	GetCursorPos(&point);
	cout << "x:" << point.x << "y:" << point.y << endl;
}
void getWindowSet() {
	HWND hq = FindWindow(L"RiotWindowClass", L"League of Legends (TM) Client");
	GetWindowRect(hq, &rect);
	GetCursorPos(&point);
	cout << point.x-rect.left<< " " << point.y-rect.top<< endl;
}
int getkeydown(int key)
{
	int t = (GetAsyncKeyState(key));
	return t;
}

bool sendmsg()
{
	return true;
}

int main()
{
	//seachPort();
	Arduino arduino;//创建Arduino对象
	arduino.init();
	//printf("1.%x\n",arduino.arduino);
	int r = 0;
	while (1) {
		if (GetAsyncKeyState(VK_SPACE) & 0xffff) {
			r = 1;
			Sleep(90);
		}
		else
			r = 0;
		if (GetAsyncKeyState(VK_CONTROL) & 0xffff)
			r = 0;

		if (r) {
			arduino.sendmsg((char)0xc9);
			while (GetAsyncKeyState(VK_SPACE) & 0xffff)
			{ 
				Sleep(10);
			}
			arduino.sendmsg((char)0xc8);
		}
		//printf("%X %X\n", GetAsyncKeyState(VK_SPACE), GetAsyncKeyState(VK_CONTROL));
		Sleep(100);
	}
	return 0;
}
