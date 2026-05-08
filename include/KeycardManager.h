#pragma once
#include <string>
#include "Keycard.h"

/**
 * @class KeycardManager
 * @brief Manages all keycard operations including generation, validation,
 *        invalidation, admin override, and automatic expiration.
 *
 * All keycards are persisted in a flat-file database (keycards.txt).
 * File format per line:
 *   <guestName> <keyID> <isValid(0|1)> <issueTime>
 */
class KeycardManager {
private:
    std::string dbPath;   ///< Path to the keycard flat-file database

    /**
     * @brief Saves a Keycard record to the database file.
     * @param keycard The Keycard to persist.
     */
    void saveToFile(const Keycard& keycard) const;

public:
    /**
     * @brief Constructs a KeycardManager with the given database path.
     * @param dbFilePath Path to the keycards database file.
     */
    explicit KeycardManager(const std::string& dbFilePath);

    /**
     * @brief Generates a new keycard for a guest and saves it.
     * @param guestName Name of the guest.
     */
    void generateKeycard(const std::string& guestName);

    /**
     * @brief Validates a keycard by its key ID.
     * @param keyID The key ID string to validate.
     * @return true if valid, false otherwise.
     */
    bool validateKeycard(const std::string& keyID) const;

    /**
     * @brief Invalidates (deactivates) a keycard by its key ID.
     * @param keyID The key ID to invalidate.
     */
    void invalidateKeycard(const std::string& keyID) const;

    /**
     * @brief Admin function: resets an existing keycard to a new guest.
     */
    void adminOverride() const;

    /**
     * @brief Scans the database and invalidates keycards older than 24 hours.
     */
    void expireOldKeycards() const;

    /**
     * @brief Prints all keycard records in a formatted table.
     */
    void listAllKeycards() const;
};
