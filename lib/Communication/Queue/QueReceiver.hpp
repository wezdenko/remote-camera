#pragma once
#include <string.h>
#include "QueConnector.hpp"


class QueReceiver: public QueConnector{
    public:
        QueReceiver(std::string name, int flags);
        virtual std::string reciveData();
        ~QueReceiver(){};
    protected:
        char buffer[MAX_SIZE];
};