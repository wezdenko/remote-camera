#pragma once
#include <functional>
#include <string>

class FileTransferer {
  public:
    virtual void transferFile(std::function<void(std::string)> transfer,
                              std::string fileName) = 0;
};