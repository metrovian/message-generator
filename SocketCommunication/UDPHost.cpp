#include "UDPHost.h"
#include "Predefined.h"

UDPHost::UDPHost()
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

    startReceiveThread();
}

UDPHost::~UDPHost()
{
    stopThread();

    closesocket(host);
    WSACleanup();

    return;
}

bool UDPHost::sendSimpleMessage(std::string _msg, std::string _ip, uint16_t _port)
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

bool UDPHost::startReceiveThread()
{
    if (flag) return false;
    flag = true;

    auto func = [&]()
        {
            sockaddr_in addr;
            int size = sizeof(addr);

            addr.sin_family = AF_INET;
            addr.sin_port = htons(12345);
            addr.sin_addr.s_addr = INADDR_ANY;

            if (bind(host, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
            {
                std::cerr << "[Host] Bind Failed : " << WSAGetLastError() << std::endl;

                closesocket(host);
                WSACleanup();

                return false;
            }

            while (flag)
            {
                char msg[BUFFER_SIZE] = { 0, };
                int ret = recvfrom(host, msg, BUFFER_SIZE, 0, (sockaddr*)&addr, &size);

                if (ret == SOCKET_ERROR) 
                {
                    std::cerr << "[Host] Receive Failed : " << WSAGetLastError() << std::endl;
                }

                else
                {
                    processReceivedMessage(std::string(msg));
                }
            }
        };

    std::thread trd = std::thread(func);
    trd.detach();

    return true;
}

bool UDPHost::stopThread()
{
    flag = false;
    return true;
}

void UDPHost::processReceivedMessage(std::string _msg)
{
    std::cerr << "[Host] " << _msg << std::endl;
}