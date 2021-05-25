#include "QueSender.hpp"
QueSender::QueSender(std::string name, int flags) : QueConnector(flags, name){};
void QueSender::sendData(std::string data) {
    auto sendData = mq_send(que, data.c_str(), data.size(), 0);
}