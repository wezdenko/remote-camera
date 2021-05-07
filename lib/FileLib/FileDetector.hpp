#pragma once
#include <filesystem>
#include <vector>
#include <functional>
#include <string>

class FileDetector{
    public:
        FileDetector(std::string path);

        std::string getPath();

        std::vector<std::string> getFilesName(std::function<bool(std::string&)> selectFunc);

        void setPath(std::string path);
    private:
        std::string path;
};