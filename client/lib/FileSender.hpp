#pragma once
#include <string>
#include <fstream>
#include  "FileTransferer.hpp"


class FileSender : public FileTransferer{
    public:
    FileSender();
    virtual void transferFile(std::function<void(std::string)> transfer, std::string fileName);

    private:
    void openFile(std::string fileName);
    std::ifstream file;
};