#include "Date.hpp"
#include <chrono>
#include <ctime>
#include <iostream>

std::string Date::getTime() {
    auto start = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(start);

    return std::ctime(&end_time);
}