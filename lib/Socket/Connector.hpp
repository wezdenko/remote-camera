#include <string>

class Connector {
  public:
    virtual bool connectToServer(std::string ipAddres, int portNumber) = 0;
    virtual bool sendData(std::string data, int size) = 0;
    virtual void closeConnection() = 0;
};