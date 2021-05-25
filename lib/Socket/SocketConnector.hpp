#include "Connector.hpp"


class SocketConnector : public Connector {
  public:
    SocketConnector(int IP_TYPE, int STREAM_TYPE);

    virtual bool connectToServer(std::string ipAddres, int portNumber);
    virtual bool sendData(std::string data, int size);
    virtual void closeConnection();


  private:
    int sock, portNumber, ipType, streamType;
    bool errorOccured;
};