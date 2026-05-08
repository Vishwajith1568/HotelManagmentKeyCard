#pragma once
#include <string>
#include <ctime>

// Returns current timestamp as formatted string
std::string getCurrentTime();

// Hashes a given key string using a polynomial rolling hash
std::string hashKey(const std::string& key);

// Generates a random 6-digit numeric string
std::string generateRandomDigits();
