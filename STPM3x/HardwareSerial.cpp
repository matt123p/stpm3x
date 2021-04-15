#include "HardwareSerial.h"
#include <windows.h>
#include <wchar.h>



HardwareSerial::HardwareSerial(int port)
{
    wchar_t PortNo[64] = { 0 }; //com port id
    swprintf_s(PortNo, 20, L"\\\\.\\COM%d", port);

    hComm = CreateFile(PortNo, //friendly name
        GENERIC_READ | GENERIC_WRITE,      // Read/Write Access
        0,                                 // No Sharing, ports cant be shared
        NULL,                              // No Security
        OPEN_EXISTING,                     // Open existing port only
        0,                                 // Non Overlapped I/O
        NULL);                             // Null for Comm Devices
    if (hComm == INVALID_HANDLE_VALUE)
    {
        throw "Port can't be opened";
    }
}

void HardwareSerial::begin(int baudRate)
{
    //Setting the Parameters for the SerialPort
    DCB dcbSerialParams = { 0 };  // Initializing DCB structure
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    auto Status = GetCommState(hComm, &dcbSerialParams); //retreives  the current settings
    if (Status == FALSE)
    {
        throw "Error to Get the Com state";
    }

    dcbSerialParams.BaudRate = baudRate;      //BaudRate = 9600
    dcbSerialParams.ByteSize = 8;             //ByteSize = 8
    dcbSerialParams.StopBits = ONESTOPBIT;    //StopBits = 1
    dcbSerialParams.Parity = NOPARITY;      //Parity = None
    Status = SetCommState(hComm, &dcbSerialParams);

    if (Status == FALSE)
    {
        throw "Error to Setting DCB Structure";
    }
}

void HardwareSerial::setTimeout(int msTimeout)
{
    //Setting Timeouts
    COMMTIMEOUTS timeouts = { 0 };  //Initializing timeouts structure
    timeouts.ReadIntervalTimeout = msTimeout;
    timeouts.ReadTotalTimeoutConstant = msTimeout;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if (SetCommTimeouts(hComm, &timeouts) == FALSE)
    {
        throw "Error to Setting Time outs";
    }
}


void HardwareSerial::write(unsigned char* data, size_t size)
{
    //Writing data to HardwareSerial Port
    DWORD BytesWritten = 0;
    auto Status = WriteFile(hComm,  // Handle to the Serialport
        data,                       // Data to be written to the port
        size,                       // No of bytes to write into the port
        &BytesWritten,              // No of bytes written to the port
        NULL);
    if (Status == FALSE)
    {
        throw "Fail to Written";
    }
}

size_t HardwareSerial::readBytes(unsigned char* data, size_t size)
{
    //Read data and store in a buffer
    size_t totalBytesRead = 0;
    DWORD NoBytesRead;
    do
    {
        auto Status = ReadFile(hComm, data + totalBytesRead, size - totalBytesRead, &NoBytesRead, NULL);
        if (Status)
        {
            totalBytesRead += NoBytesRead;
        }
        else
        {
            NoBytesRead = 0;
        }
    } while (NoBytesRead > 0 && totalBytesRead < size);

    return totalBytesRead;
}



