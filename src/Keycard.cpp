#include "../include/Keycard.h"
#include "../include/Utils.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Keycard::Keycard(const std::string& name) {
    guestName = name;
    keyID     = generateKeyID();
    isValid   = true;
    issueTime = getCurrentTime();
}

std::string Keycard::generateKeyID() {
    srand(static_cast<unsigned int>(time(0)) + rand());
    return hashKey(generateRandomDigits());
}

void Keycard::displayKey() const {
    std::cout << "\n┌─────────────────────────────────────┐" << std::endl;
    std::cout << "│           KEYCARD ISSUED            │" << std::endl;
    std::cout << "├─────────────────────────────────────┤" << std::endl;
    std::cout << "│  Guest  : " << guestName              << std::endl;
    std::cout << "│  Key ID : " << keyID                  << std::endl;
    std::cout << "│  Time   : " << issueTime              << std::endl;
    std::cout << "│  Status : ACTIVE ✓                  │" << std::endl;
    std::cout << "└─────────────────────────────────────┘" << std::endl;
}
