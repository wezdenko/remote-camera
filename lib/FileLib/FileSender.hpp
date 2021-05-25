#pragma once
#include "FileTransferer.hpp"
#include <fstream>
#include <string>


class FileSender : public FileTransferer {
  public:
    FileSender();
    virtual void transferFile(std::function<void(std::string)> transfer,
                              std::string fileName);

  private:
    void openFile(std::string fileName);
    std::ifstream file;
};