#include "ReciveServer.hpp"


ReciveServer::ReciveServer(Saver saver, int IP_TYPE, int STREAM_TYPE): dataSaver(saver), ipType(IP_TYPE), streamType(STREAM_TYPE){};

void ReciveServer::createServer(int portNumber){
    sock = socket(ipType, streamType, 0);
    if(sock <= 0){
        std::cerr<<"Cant create socket!";
        return ;
    }
    //Bind socket to IP port
    sockaddr_in hint;
    hint.sin_family = ipType;
    hint.sin_port = htons(portNumber);
    inet_pton(ipType, "0.0.0.0", &hint.sin_addr);

    if(bind(sock, (const struct sockaddr*)&hint, sizeof(hint)) == -1){
        std::cerr<<"Cant bind to ip port!";
        return ;
    }
    if(listen(sock, SOMAXCONN) == -1){
        std::cerr<<"Cant listen!";
        return ;
    }
}
void ReciveServer::acceptConnection(){
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];

    clientSock = accept(sock, (struct sockaddr*)&client, &clientSize);
    if(clientSock == -1){
        std::cout<<"Problem with cleint connection!";
        return ;
    }
}
void ReciveServer::openServer(){
    while(true){
        acceptConnection();
        reciveData();
    }
}
void ReciveServer::reciveData(){
    std::string name = reciveName();
    dataSaver(name.c_str());
    char buffer[DATA_SIZE];
    while(true){
        memset(buffer, 0, DATA_SIZE);
        int bytesRecv = recv(clientSock, buffer, DATA_SIZE, 0);
        if(bytesRecv == -1){
            std::cerr << "There was a connecting isse "<<std::endl;
            break;
        }
        if(bytesRecv == 0){
            std::cout<<std::endl<<"The client disconected"<< std::endl;
            break;
        }
        dataSaver(buffer);
    }
    close(clientSock);
    dataSaver("close");
}
std::string ReciveServer::reciveName(){
    char nameBuffer[FILE_NAME_SIZE];
    int bytesRecv = recv(clientSock, nameBuffer, FILE_NAME_SIZE, 0);
    std::string name(nameBuffer);
    memset(nameBuffer, 0, FILE_NAME_SIZE);
    return name;

}
void ReciveServer::closeServer(){
    close(sock);
}