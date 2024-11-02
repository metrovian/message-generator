#include "TCPClient.h"
#include "Predefined.h"

bool TCPClient::connect()
{
    WSADATA wsaData;
    int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (ret != 0) 
    {
        std::cerr << "[Client] WSAStartup Failed : " << ret << std::endl;
        return false;
    }

    client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (client == INVALID_SOCKET) 
    {
        std::cerr << "[Client] Socket Creation Failed : " << WSAGetLastError() << std::endl;
        WSACleanup();

        return false;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

    if (::connect(client, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
        std::cerr << "[Client] Connection Failed : " << WSAGetLastError() << std::endl;
        closesocket(client);
        WSACleanup();

        return false;
    }

    else
    {
        startReceiveThread();
    }

    return true;
}

bool TCPClient::disconnect()
{
    stopThread();

    closesocket(client);
    WSACleanup();

    return true;
}

bool TCPClient::sendSimpleMessage(std::string _msg)
{
    send(client, _msg.c_str(), strlen(_msg.c_str()), 0);
    return true;
}

bool TCPClient::startReceiveThread()
{
    if (flag) return false;
    flag = true;

    auto func = [&]()
        {
            while (flag)
            {
                char msg[BUFFER_SIZE] = { 0, };
                int ret = recv(client, msg, BUFFER_SIZE, 0);

                if (ret == 0)
                {
                    std::cerr << "[Server] Disconnected" << std::endl;
                    break;
                }

                else if (ret < 0)
                {
                    std::cerr << "[Server] Receive Failed : " << WSAGetLastError() << std::endl;
                    break;
                }

                else
                {
                    processReceivedMessage(std::string(msg));
                }
            }
        };

    std::thread trd = std::thread(func);
    trd.detach();
}

bool TCPClient::stopThread()
{
    flag = false;
    return true;
}

void TCPClient::processReceivedMessage(std::string _msg)
{
    std::cerr << "[Server] " << _msg << std::endl;
}
