#include "UDP.h"
#include "Predefined.h"

UDP::UDP()
{
    WSADATA wsaData;
    int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (ret != 0) 
    {
        std::cerr << "[Host] WSAStartup Failed : " << ret << std::endl;
        return;
    }

    host = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (host == INVALID_SOCKET) 
    {
        std::cerr << "[Host] Socket Creation Failed : " << WSAGetLastError() << std::endl;
        WSACleanup();

        return;
    }

    static int opt = 1;
    setsockopt(host, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
}

UDP::~UDP()
{
    stopThread();

    closesocket(host);
    WSACleanup();

    return;
}

bool UDP::sendSimpleMessage(std::string _msg, std::string _ip, uint16_t _port)
{
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(_port);
    inet_pton(AF_INET, _ip.c_str(), &addr.sin_addr);

    int ret = sendto(host, _msg.c_str(), _msg.size(), 0, (sockaddr*)&addr, sizeof(addr));

    if (ret == SOCKET_ERROR) 
    {
        std::cerr << "[Host] Send Failed : " << WSAGetLastError() << std::endl;
        return false;
    }

    return true;
}

bool UDP::startReceiveThread(uint16_t _port)
{
    if (flag.find(_port) != flag.end()) return false;
    flag.insert(_port);

    auto func = [&]()
        {
            sockaddr_in addr;
            int size = sizeof(addr);

            addr.sin_family = AF_INET;
            addr.sin_port = htons(_port);
            addr.sin_addr.s_addr = INADDR_ANY;

            if (bind(host, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
            {
                std::cerr << "[Host] Bind Failed : " << WSAGetLastError() << std::endl;

                closesocket(host);
                WSACleanup();

                return false;
            }

            while (flag.find(_port) != flag.end())
            {
                char msg[BUFFER_SIZE] = { 0, };
                int ret = recvfrom(host, msg, BUFFER_SIZE, 0, (sockaddr*)&addr, &size);

                if (ret == SOCKET_ERROR) 
                {
                    std::cerr << "[Host] Receive Failed : " << WSAGetLastError() << std::endl;
                }

                else
                {
                    processReceivedMessage(std::string(msg, ret), _port);
                }
            }
        };

    std::thread trd = std::thread(func);
    trd.detach();

    return true;
}

bool UDP::stopThread(uint16_t _port)
{
    flag.erase(_port);
    return true;
}

bool UDP::stopThread()
{
    flag.clear();
    return true;
}

void UDP::processReceivedMessage(std::string _msg, uint16_t _port)
{
    std::cerr << "[Host " << _port << "] " << _msg << std::endl;
}