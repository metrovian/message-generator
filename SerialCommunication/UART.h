#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include <iostream>

class UART
{
protected: /* handle */
    HANDLE com = NULL;

protected: /* config */
    std::string port = "COM5";
    DWORD baud = 9600;
    BYTE data = 8;
    BYTE par = 0;
    BYTE stop = 0;

public: /* connection */
    bool open();
    bool close();

public: /* search */
    static std::vector<std::string> searchPorts();
};