#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <regex>

namespace mySocket {
    constexpr int BufferLen = 512;

    class TwitchSocket {
    private:
        std::vector<char> buffer = std::vector<char>(BufferLen);

        SOCKET Connection;
    public:

        int send(const std::string& info);
        std::string recieve();

        TwitchSocket(const TwitchSocket&) = delete;
        TwitchSocket& operator = (const TwitchSocket&) = delete;

        TwitchSocket(SOCKET _Connection);

    };

}