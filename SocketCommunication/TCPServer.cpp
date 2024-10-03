#include "TCPServer.h"

bool TCPServer::open()
{
    WSADATA wsaData;

    int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (ret != 0)
    {
        std::cerr << "WSAStartup Failed : " << ret << std::endl;
        return false;
    }

    server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (server == INVALID_SOCKET)
    {
        std::cerr << "Socket Creation Failed : " << WSAGetLastError() << std::endl;
        WSACleanup();

        return false;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(server, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
        std::cerr << "Bind Failed : " << WSAGetLastError() << std::endl;
        closesocket(server);
        WSACleanup();

        return false;
    }

    if (listen(server, max) == SOCKET_ERROR) 
    {
        std::cerr << "Listen Failed : " << WSAGetLastError() << std::endl;
        closesocket(server);
        WSACleanup();
        
        return false;
    }

    return true;
}

bool TCPServer::close()
{
    for (uint64_t i = client.size(); i > 0; --i)
    {
        closesocket(client[i - 1]);
        client.pop_back();
    }
    
    closesocket(server);
    WSACleanup();

    return false;
}

bool TCPServer::startAcceptThread()
{
    if (flag) return false;

    flag = true;

    auto func = [&]() 
        {
            while (flag)
            {
                sockaddr_in addr;
                int aize = sizeof(addr);

                client.push_back(accept(server, (sockaddr*)&addr, &aize));

                if (client[client.size() - 1] == INVALID_SOCKET) 
                {
                    std::cerr << "Accept Failed: " << WSAGetLastError() << std::endl;

                    closesocket(client[client.size() - 1]);
                    client.pop_back();
                }

                else
                {
                    startReceiveThread(client.size() - 1);
                }
            }
        };

    std::thread trd = std::thread(func);
    trd.detach();

    return true;
}

bool TCPServer::startReceiveThread(uint64_t _idx)
{
    if (_idx > client.size() - 1) return false;

    auto func = [&]()
        {
            while (client[_idx])
            {

            }
        };

    return true;
}

bool TCPServer::stopThread()
{
    flag = false;
    return true;
}

void TCPServer::processReceivedMessage(std::string _msg)
{
}
