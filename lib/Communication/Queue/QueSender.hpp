#pragma once
#include "QueConnector.hpp"


class QueSender: public QueConnector{
    public:
        QueSender(std::string name, int flags);
        virtual void sendData(std::string data);
        ~QueSender(){};
};