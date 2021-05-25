#include "QueReceiver.hpp"

QueReceiver::QueReceiver(std::string name, int flags)
    : QueConnector(flags, name){};
std::string QueReceiver::reciveData() {
    memset(buffer, 0, MAX_SIZE);
    auto recivedData = mq_receive(que, buffer, MAX_SIZE, NULL);
    return std::string(buffer);
}