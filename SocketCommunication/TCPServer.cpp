#include "TCPServer.h"
#include "Predefined.h"

bool TCPServer::open()
{
    WSADATA wsaData;
    int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (ret != 0)
    {
        std::cerr << "[Server] WSAStartup Failed : " << ret << std::endl;
        return false;
    }

    server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (server == INVALID_SOCKET)
    {
        std::cerr << "[Server] Socket Creation Failed : " << WSAGetLastError() << std::endl;
        WSACleanup();

        return false;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(server, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
        std::cerr << "[Server] Bind Failed : " << WSAGetLastError() << std::endl;
        closesocket(server);
        WSACleanup();

        return false;
    }

    if (listen(server, max) == SOCKET_ERROR) 
    {
        std::cerr << "[Server] Listen Failed : " << WSAGetLastError() << std::endl;
        closesocket(server);
        WSACleanup();
        
        return false;
    }

    startAcceptThread();

    return true;
}

bool TCPServer::close()
{
    stopThread();

    for (uint64_t i = client.size(); i > 0; --i)
    {
        closesocket(client[i - 1]);
        client.pop_back();
    }
    
    closesocket(server);
    WSACleanup();

    return true;
}

bool TCPServer::sendSimpleMessage(std::string _msg, uint64_t _idx)
{
    if (_idx > client.size()) return false;

    send(client[_idx], _msg.c_str(), strlen(_msg.c_str()), 0);
    return true;
}

bool TCPServer::sendSimpleMessage(std::string _msg)
{
    for (uint64_t i = 0; i < client.size(); ++i)
    {
        if (!sendSimpleMessage(_msg, i)) return false;
    }

    return true;
}

bool TCPServer::startAcceptThread()
{
    if (flag) return false;
    flag = true;

    sockaddr_in addr;
    int size = sizeof(addr);

    auto func = [&]() 
        {
            while (flag)
            {
                client.push_back(accept(server, (sockaddr*)&addr, &size));

                if (client[client.size() - 1] == INVALID_SOCKET) 
                {
                    std::cerr << "[Server] Accept Failed: " << WSAGetLastError() << std::endl;

                    closesocket(client[client.size() - 1]);
                    client.pop_back();
                }

                else
                {
                    std::cerr << "[Client " << client.size() - 1 << "] Connected" << std::endl;
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
            while (flag)
            {
                char msg[BUFFER_SIZE] = { 0, };
                int ret = recv(client[_idx], msg, BUFFER_SIZE, 0);

                if (ret == 0)
                {
                    std::cerr << "[Client " << _idx << "] Disconnected" << std::endl;
                    break;
                }

                else if (ret < 0)
                {
                    std::cerr << "[Client " << _idx << "] Receive Failed : " << WSAGetLastError() << std::endl;
                    break;
                }

                else
                {
                    processReceivedMessage(std::string(msg), _idx);
                }
            }
        };

    std::thread trd = std::thread(func);
    trd.detach();

    return true;
}

bool TCPServer::stopThread()
{
    flag = false;
    return true;
}

void TCPServer::processReceivedMessage(std::string _msg, uint64_t _idx)
{
    std::cerr << "[Client " << _idx << "] " << _msg << std::endl;
}
