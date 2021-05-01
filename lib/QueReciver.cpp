#include "QueReciver.hpp"

QueReciver::QueReciver(std::string name, int flags):QueConnector(flags, name){};
std::string QueReciver::reciveData(){
    memset(buffer, 0, MAX_SIZE);
    auto recivedData = mq_receive(que, buffer, MAX_SIZE, NULL);
    return std::string(buffer);
}