#pragma once
#define MAX_SIZE 1024
#include <string>
#include <fcntl.h>
#include <sys/types.h>
#include <mqueue.h>
#include <unistd.h>
#include "../CommunicationStructs.hpp"



class QueConnector{
    public:
        QueConnector(int flags, std::string queName);
        virtual ~QueConnector();
    protected:
        mqd_t que;
        std::string queName;
};