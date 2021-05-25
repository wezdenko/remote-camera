#pragma once
#include <filesystem>
#include <functional>
#include <string>
#include <vector>

class FileDetector {
  public:
    FileDetector(std::string path);

    std::string getPath();

    std::vector<std::string>
    getFilesName(std::function<bool(std::string &)> selectFunc);

    void setPath(std::string path);

  private:
    std::string path;
};