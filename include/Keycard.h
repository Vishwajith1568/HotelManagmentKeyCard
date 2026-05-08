#pragma once
#include <string>

/**
 * @class Keycard
 * @brief Represents a hotel room keycard with a unique ID, guest name,
 *        validity status, and issue timestamp.
 */
class Keycard {
public:
    std::string keyID;
    std::string guestName;
    bool isValid;
    std::string issueTime;

    /**
     * @brief Constructs a new Keycard for the specified guest.
     * @param name Guest's full name.
     */
    explicit Keycard(const std::string& name);

    /**
     * @brief Generates a hashed key ID from random digits.
     * @return Hashed key string.
     */
    std::string generateKeyID();

    /**
     * @brief Prints the keycard info to stdout.
     */
    void displayKey() const;
};
