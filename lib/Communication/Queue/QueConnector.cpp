#include "QueConnector.hpp"

QueConnector::QueConnector(int flags, std::string queueName)
    : queName(queueName) {
    struct mq_attr attr;
    /* initialize the queue attributes */
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    que = mq_open(queName.c_str(), flags, 0644, &attr);
}
QueConnector::~QueConnector() {
    mq_close(que);
    mq_unlink(queName.c_str());
};