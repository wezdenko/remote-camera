#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include "SocketConnector.hpp"

SocketConnector::SocketConnector(int IP_TYPE, int STREAM_TYPE)
{
    this->ipType = IP_TYPE;
    this->streamType = STREAM_TYPE;
    this->sock = socket(ipType, streamType, 0);
    if(this->sock == -1){
        this->errorOccured = true;
        std::cerr<<"Cannot create Socket!";
    };

};
bool SocketConnector::connectToServer(std::string ipAddress, int portNumber)
{

    sockaddr_in hint;
    hint.sin_family = this->ipType;
    hint.sin_port = htons(portNumber);
    inet_pton(this->ipType, ipAddress.c_str(), &hint.sin_addr);

    int connection = connect(sock, (const sockaddr*)&hint, sizeof(hint));

    return connection == -1? false : true;
}

void SocketConnector::closeConnection()
{
    close(this->sock);
}

bool SocketConnector::sendData(std::string data, int size){
    int sendRes = send(sock, data.c_str(), size, 0);
    return sendRes == -1 ? false : true;
}