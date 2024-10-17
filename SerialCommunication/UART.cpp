#include "UART.h"

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
