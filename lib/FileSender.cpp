#include "FileSender.hpp"
#include <iostream>

FileSender::FileSender()
{

}
void FileSender::transferFile(std::function<void(std::string)> transfer, std::string fileName){
    openFile(fileName+".jpeg");
    transfer(fileName);
    int data = file.get();
    while(file){
        transfer(std::to_string(data));
        data = file.get();
    }
    file.close();
}
void FileSender::openFile(std::string fileName){
    this->file.open(fileName);
}