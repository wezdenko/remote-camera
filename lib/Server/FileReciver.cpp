#include "FileReciver.hpp"
#include <iostream>
FileReciver::FileReciver(){};
void FileReciver::createFile(std::string fileName) {
    this->fileStream.open(fileName);
}
void FileReciver::saveData(const char *data) {
    std::string str(data);
    this->fileStream.put(std::stoi(str));
}
void FileReciver::closeFile() { this->fileStream.close(); }
