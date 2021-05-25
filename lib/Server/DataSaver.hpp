#pragma once
#include <istream>
class DataSaver {
  public:
    virtual void saveData(const char *data) = 0;
};