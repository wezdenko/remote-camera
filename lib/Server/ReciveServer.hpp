#pragma once
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <functional>
#include "Server.hpp"


using Saver = std::function<void(const char*)>;

class ReciveServer: public Server{
    public:
        ReciveServer(Saver, int IP_TYPE, int STREAM_TYPE);
        virtual void createServer(int portNumber);
        virtual void openServer();
        virtual void closeServer();
    protected:
        virtual void acceptConnection();
        virtual void reciveData();
        virtual std::string reciveName();
    private:
        int sock, clientSock, ipType, streamType;
        Saver dataSaver;
};