#pragma once
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include "../CommunicationStructs.hpp"


class MemoryAllocator{
    public:
        MemoryAllocator(std::string memoryName);

        Shmbuf* getBuffer();

        virtual ~MemoryAllocator();
    protected:
        int sharedMemmory;
        Shmbuf* buffer; 
        std::string memoryName;

};