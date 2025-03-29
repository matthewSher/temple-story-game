#include "../../include/utils/logging.h"

#include <iostream>

void errorLog(const std::string& funcName, const std::string& error) {
    std::cout << "[ERROR] " << funcName << ": " << error << std::endl;
}

void infoLog(const std::string& funcName, const std::string& info) {
    std::cout << "[INFO] " << funcName << ": " << info << std::endl;
}