#pragma once
#include <string.h>
#include "QueConnector.hpp"


class QueReciver: public QueConnector{
    public:
        QueReciver(std::string name, int flags);
        virtual std::string reciveData();
        ~QueReciver(){};
    protected:
        char buffer[MAX_SIZE];
};