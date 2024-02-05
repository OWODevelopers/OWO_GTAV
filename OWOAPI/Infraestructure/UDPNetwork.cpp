#ifdef _WIN32
#include "UDPNetwork.h"

#define BUFLEN 1024

using namespace OWOGame;

char* ToChars(owoString& value) { return const_cast<char*>(value.data()); }

void UDPNetwork::Initialize()
{
    WSADATA wsdata = WSADATA();

    if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0)
    {
        throw std::exception("WSA not initialized");
    }

    if ((mySocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
    {
        throw std::exception("An error ocurred while initializing the OWO UDP socket");
    }

    u_long mode = 1;
    if (ioctlsocket(mySocket, FIONBIO, &mode) == SOCKET_ERROR)
    {
        throw std::exception("An error ocurred while configuring OWO socket");
    }

    char broadcast = 1;
    if (setsockopt(mySocket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast) == SOCKET_ERROR)
    {
        throw std::exception("An error ocurred while configuring OWO socket");
    }
}

void UDPNetwork::Connect(owoString serverIp)
{
    connectedAddressees.push_back(serverIp);
    state = ConnectionState::Connected;
}

ConnectionState OWOGame::UDPNetwork::GetState()
{
    return state;
}

void OWOGame::UDPNetwork::SetState(ConnectionState state)
{
    this->state = state;
}

owoVector<owoString> OWOGame::UDPNetwork::GetConnectedAddressee()
{
    return connectedAddressees;
}

owoString UDPNetwork::Listen(owoString& senderIp)
{
    struct sockaddr_in sender;
    int slen = sizeof(sender);

    char buf[BUFLEN];

    fflush(stdout);
    memset(buf, 0, BUFLEN);

    recvfrom(mySocket, buf, BUFLEN, 0, (struct sockaddr*)&sender, &slen);

    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(sender.sin_addr), str, INET_ADDRSTRLEN);

    senderIp = str;
    return buf;
}

void UDPNetwork::Send(owoString message)
{
    SendTo(message, connectedAddressees[0]);
}

void UDPNetwork::SendTo(owoString message, owoString ip)
{
    sockaddr_in RecvAddr;

    if (inet_pton(AF_INET, ToChars(ip), &(RecvAddr.sin_addr.s_addr)) != 1)
    {
        throw std::exception("the ip provided is not valid");
    }

    RecvAddr.sin_family = AF_INET;
    RecvAddr.sin_port = htons(54020);

    if (sendto(mySocket, ToChars(message), strlen(ToChars(message)), 0, (SOCKADDR*)&RecvAddr, sizeof(RecvAddr)) == SOCKET_ERROR)
    {
        throw std::exception("[OWO] An error occurred while trying to send a sensation");
    }
}

void UDPNetwork::Disconnect()
{
    state = ConnectionState::Disconnected;
    closesocket(mySocket);
    WSACleanup();
}
#endif