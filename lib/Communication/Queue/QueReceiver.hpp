#pragma once
#include "QueConnector.hpp"
#include <string.h>


class QueReceiver : public QueConnector {
  public:
    QueReceiver(std::string name, int flags);
    virtual std::string reciveData();
    ~QueReceiver(){};

  protected:
    char buffer[MAX_SIZE];
};