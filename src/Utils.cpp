#include "../include/Utils.h"
#include <cstdlib>
#include <ctime>
#include <sstream>

std::string getCurrentTime() {
    time_t now = time(0);
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", localtime(&now));
    return std::string(buffer);
}

std::string hashKey(const std::string& key) {
    unsigned int hash = 0;
    for (char c : key) {
        hash = (hash * 31) + c;
    }
    return std::to_string(hash);
}

std::string generateRandomDigits() {
    std::string digits = "";
    for (int i = 0; i < 6; i++) {
        digits += std::to_string(rand() % 10);
    }
    return digits;
}
