#include "FileDetector.hpp"

FileDetector::FileDetector(std::string dirPath) : path(dirPath){};

std::string FileDetector::getPath() { return path; }

std::vector<std::string>
FileDetector::getFilesName(std::function<bool(std::string &)> selectFunc) {
    std::vector<std::string> filesNames;
    for (const auto &file : std::filesystem::directory_iterator(path)) {
        auto fileName = file.path().u8string();
        if (selectFunc(fileName))
            filesNames.push_back(fileName);
    }
    return filesNames;
}

void FileDetector::setPath(std::string path) { this->path = path; }