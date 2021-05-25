#pragma once
#include "../CommunicationStructs.hpp"
#include <fcntl.h>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


class MemoryAllocator {
  public:
    MemoryAllocator(std::string memoryName);

    Shmbuf *getBuffer();

    virtual ~MemoryAllocator();

  protected:
    int sharedMemmory;
    Shmbuf *buffer;
    std::string memoryName;
};