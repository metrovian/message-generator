#include "UART.h"

bool UART::open()
{
    if (com != NULL) return false;

    com = CreateFileA
    (
        port.c_str(), 
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (com == INVALID_HANDLE_VALUE) 
    {
        std::cerr << "[" << port << "] Open Failed" << std::endl;
        return false;
    }

    DCB dcbs = { 0 };
    dcbs.DCBlength = sizeof(dcbs);

    if (!GetCommState(com, &dcbs)) 
    {
        std::cerr << "[" << port << "] Status Check Failed" << std::endl;
        close();

        return false;
    }

    dcbs.BaudRate = baud;
    dcbs.ByteSize = data;
    dcbs.Parity = par;
    dcbs.StopBits = stop;

    if (!SetCommState(com, &dcbs)) 
    {
        std::cerr << "[" << port << "] Frame Configuration Failed" << std::endl;
        close();

        return false;
    }

    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(com, &timeouts)) 
    {
        std::cerr << "[" << port << "] Timeout Configuration Failed" << std::endl;
        close();

        return false;
    }

    return true;
}

bool UART::close()
{
    if (com != NULL) 
    {
        CloseHandle(com);
        com = NULL;

        return true;
    }

    return false;
}

std::vector<std::string> UART::searchPorts()
{
    std::vector<std::string> ret;

    for (unsigned char i = 0; i < 255; ++i)
    {
        std::string name = "\\\\.\\COM" + std::to_string(i + 1);
        HANDLE hport = CreateFileA(name.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

        if (hport != INVALID_HANDLE_VALUE)
        {
            ret.push_back("COM" + std::to_string(i));
            CloseHandle(hport);
        }
    }

    return ret;
}
