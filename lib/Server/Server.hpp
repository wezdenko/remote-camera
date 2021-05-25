#pragma once
class Server {
  public:
    virtual void createServer(int portNumber) = 0;
    virtual void openServer() = 0;
    virtual void closeServer() = 0;

  protected:
    virtual void acceptConnection() = 0;
    virtual void reciveData() = 0;
};