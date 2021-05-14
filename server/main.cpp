#include <memory>
#include <netdb.h>
#include <iostream>
#include <string>
#include "Def.h"
#include "Server/FileReciver.hpp"
#include "Server/ReciveServer.hpp"

int main(){
    std::unique_ptr<FileReciver> fileReciver(new FileReciver());
    auto fileRecive = [&](const char* data){
        std::string recivedData(data);
        if(recivedData == "close") fileReciver->closeFile();
        else if(recivedData.size() > DATA_SIZE) fileReciver->createFile(recivedData+".jpeg");
        else fileReciver->saveData(data);
    };
    std::unique_ptr<ReciveServer> server(new ReciveServer(fileRecive, AF_INET, SOCK_STREAM));
    server->createServer(54000);
    server->openServer();
    server->closeServer();
    return 0;
}