#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include <iostream>

class UART
{
public:
    static std::vector<std::string> searchPorts();
};