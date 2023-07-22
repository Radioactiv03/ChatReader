#include "TwitchSocket.h"


namespace mySocket {



    int TwitchSocket::send(const std::string& info)
    {
        return ::send(Connection, info.c_str(), info.length(), NULL);
    }
    std::string TwitchSocket::recieve()
    {
        std::vector<char> buffer(BufferLen);

        int Bytes = recv(Connection, buffer.data(), BufferLen, NULL);
        return std::string(buffer.begin(), buffer.begin() + Bytes);
    }



    TwitchSocket::TwitchSocket(SOCKET _Connection)
    {
        Connection = _Connection;
    }
}