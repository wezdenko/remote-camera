#include <iostream>
#include <arpa/inet.h>
#include "SocketConnector.hpp"
#include "FileSender.hpp"
#include "VectorSender.hpp"
#include <memory>

int main()
{
    std::vector<int> vec = {5,6,7,8,9,10};
    auto vecSender = std::make_unique<VectorSender<int>>(vec);
    FileTransferer* dataTransferer;
    dataTransferer = vecSender.get();
    dataTransferer->transferFile([&](std::string data){
        std::cout<<data<<"\n";
    }, "TEST");

    // auto connection = SocketConnector(AF_INET, SOCK_STREAM);
    // if(!connection.connectToServer("172.17.0.1", 54000)){
    //     std::cerr<<"CANT CONNECT TO SERVER!";
    //     return -1;
    // }
    // std::cout<<"CONNECTED!";
    // auto sender = FileSender();
    // sender.transferFile([&](std::string data){
    //     if(data.size() > 4) connection.sendData(data, 20);
    //     else connection.sendData(data, 3);
    // }, "fotodziala");
    // connection.closeConnection();
    // return 0;

}