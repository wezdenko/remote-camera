#pragma once
#include <vector>
#include "FileTransferer.hpp"

template<typename T>
class VectorSender: public FileTransferer{
    public:
        VectorSender(const std::vector<T>& dataVec): data(dataVec){};
        virtual void transferFile(std::function<void(std::string)> transfer, std::string fileName){
            transfer(fileName);
            for(const auto& singleData : data){
                transfer(std::to_string(singleData));
            }
            transfer("qit");
        }
        void setVector(const std::vector<T>& data){
            this->data = data;
        }
    private:
        std::vector<T> data;
};