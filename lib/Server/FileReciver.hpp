#pragma once
#include <fstream>
#include <string>


class FileReciver {
  public:
    FileReciver();
    virtual void saveData(const char *data);
    virtual void createFile(std::string fileName);
    virtual void closeFile();

  private:
    std::ofstream fileStream;
};