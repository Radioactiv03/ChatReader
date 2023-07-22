#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <string>
#include <regex>
#include <chrono>
#include "TwitchSocket.h"

#pragma comment(lib,"Winmm.lib")
#pragma comment(lib,"Ws2_32.lib")



int main()
{
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    addrinfo hints{};
    addrinfo* result;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        return -1;
    }
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo("irc.chat.twitch.tv", "6667", &hints, &result))
    {
        return -1;
    }

    ConnectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ConnectSocket == INVALID_SOCKET)
    {
        std::cout << "invalid socket" << std::endl;
        freeaddrinfo(result);
        WSACleanup();
        return -1;
    }

    if (connect(ConnectSocket, result->ai_addr, result->ai_addrlen) == SOCKET_ERROR)
    {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
    }

    freeaddrinfo(result);
    if (ConnectSocket == INVALID_SOCKET)
    {
        WSACleanup();
        return -1;
    }

    std::string password = "PASS ASIDUASN\r\n";
    std::string NICK = "NICK justinfan5187\r\n";

    mySocket::TwitchSocket twitch(ConnectSocket);
    twitch.send(password);
    twitch.send(NICK);

    std::string reply_connect = twitch.recieve();

    twitch.send("JOIN #elajjaz\r\n");

    std::regex re(R"RE(^:([^!]+)![^@]+@[^\.]+\.tmi\.twitch\.tv PRIVMSG #([^\s]+) :(.*))RE");
    std::smatch match;

    while (1)
    {
        std::string reply = twitch.recieve();
        
        //PARSING


        std::regex_search(reply,match, re);

        std::cout << match[1] << ": " << match[3] << std::endl;
    }
    return 0;
}


