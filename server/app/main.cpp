#include <memory>
#include <netdb.h>
#include <iostream>
#include <string>
#include "FileReciver.hpp"
#include "ReciveServer.hpp"

int main(){
    std::unique_ptr<FileReciver> fileReciver(new FileReciver());
    auto fileRecive = [&](const char* data, bool isCommand){
        if(isCommand){ 
            std::string command(data);
            if(command == "close") fileReciver->closeFile();
            else fileReciver->createFile(command+".jpeg");
            std::cout<<data;
            }
        else fileReciver->saveData(data);
    };
    std::unique_ptr<ReciveServer> server(new ReciveServer(fileRecive, AF_INET, SOCK_STREAM));
    server->createServer(54000);
    server->openServer();
    server->closeServer();
    return 0;
}