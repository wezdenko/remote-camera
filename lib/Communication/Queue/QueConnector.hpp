#pragma once
#define MAX_SIZE 1024
#include "../CommunicationStructs.hpp"
#include <fcntl.h>
#include <mqueue.h>
#include <string>
#include <sys/types.h>
#include <unistd.h>


class QueConnector {
  public:
    QueConnector(int flags, std::string queName);
    virtual ~QueConnector();

  protected:
    mqd_t que;
    std::string queName;
};