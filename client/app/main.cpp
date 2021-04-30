#include <iostream>
#include <arpa/inet.h>
#include "SocketConnector.hpp"
#include "FileSender.hpp"

int main()
{
    auto connection = SocketConnector(AF_INET, SOCK_STREAM);
    if(!connection.connectToServer("172.17.0.1", 54000)){
        std::cerr<<"CANT CONNECT TO SERVER!";
        return -1;
    }
    std::cout<<"CONNECTED!";
    auto sender = FileSender();
    sender.transferFile([&](std::string data){
        if(data.size() > 4) connection.sendData(data, 20);
        else connection.sendData(data, 3);
    }, "fotodziala");
    connection.closeConnection();
    return 0;

}