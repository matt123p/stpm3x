#pragma once
#include <windows.h>

class HardwareSerial
{
private:
	HANDLE hComm;  // Handle to the Serial port

public:
	HardwareSerial(int port);
	void begin(int baudRate);
	void setTimeout(int msTimeout);

	void write(unsigned char* data, size_t size);
	size_t readBytes(unsigned char* data, size_t size);
};

