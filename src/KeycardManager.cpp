#include "../include/KeycardManager.h"
#include "../include/Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstdio>

using namespace std;

KeycardManager::KeycardManager(const std::string& dbFilePath)
    : dbPath(dbFilePath) {}

void KeycardManager::saveToFile(const Keycard& keycard) const {
    ofstream file(dbPath, ios::app);
    if (!file) {
        cerr << "[ERROR] Unable to save keycard data to: " << dbPath << endl;
        return;
    }
    file << keycard.guestName << " "
         << keycard.keyID     << " "
         << keycard.isValid   << " "
         << keycard.issueTime << "\n";
    file.close();
    cout << "✓ Keycard saved to database." << endl;
}

void KeycardManager::generateKeycard(const std::string& guestName) {
    Keycard newKey(guestName);
    newKey.displayKey();
    saveToFile(newKey);
}

bool KeycardManager::validateKeycard(const std::string& keyID) const {
    ifstream file(dbPath);
    if (!file) {
        cerr << "[ERROR] Unable to open keycard database: " << dbPath << endl;
        return false;
    }

    string name, key, timeIssued;
    bool valid;
    while (file >> name >> key >> valid) {
        getline(file, timeIssued);
        if (key == keyID) {
            if (valid) {
                cout << "\n✅  Access Granted! Welcome back, " << name << "!" << endl;
                return true;
            } else {
                cout << "\n❌  Access Denied! Key is expired or invalidated." << endl;
                return false;
            }
        }
    }
    cout << "\n❌  Access Denied! Key not found in system." << endl;
    return false;
}

void KeycardManager::invalidateKeycard(const std::string& keyID) const {
    ifstream file(dbPath);
    string tmpPath = dbPath + ".tmp";
    ofstream temp(tmpPath);

    if (!file || !temp) {
        cerr << "[ERROR] Unable to access keycard database!" << endl;
        return;
    }

    string name, key, timeIssued;
    bool valid;
    bool found = false;

    while (file >> name >> key >> valid) {
        getline(file, timeIssued);
        if (key == keyID) {
            found = true;
            temp << name << " " << key << " " << 0 << " " << timeIssued << "\n";
        } else {
            temp << name << " " << key << " " << valid << " " << timeIssued << "\n";
        }
    }
    file.close();
    temp.close();
    remove(dbPath.c_str());
    rename(tmpPath.c_str(), dbPath.c_str());

    if (found)
        cout << "✓ Keycard [" << keyID << "] has been invalidated." << endl;
    else
        cout << "⚠  Key not found in the system." << endl;
}

void KeycardManager::adminOverride() const {
    string enteredKey, newGuest;
    cout << "Enter Key ID to Reset : ";
    cin  >> enteredKey;
    cout << "Enter New Guest Name  : ";
    cin  >> newGuest;

    ifstream file(dbPath);
    string tmpPath = dbPath + ".tmp";
    ofstream temp(tmpPath);

    if (!file || !temp) {
        cerr << "[ERROR] Unable to access keycard database!" << endl;
        return;
    }

    string name, key, timeIssued;
    bool valid;
    bool found = false;

    while (file >> name >> key >> valid) {
        getline(file, timeIssued);
        if (key == enteredKey) {
            found = true;
            Keycard newKey(newGuest);
            temp << newGuest       << " "
                 << newKey.keyID   << " "
                 << 1              << " "
                 << getCurrentTime() << "\n";
            cout << "✓ Keycard reset. New Key ID for " << newGuest
                 << ": " << newKey.keyID << endl;
        } else {
            temp << name << " " << key << " " << valid << " " << timeIssued << "\n";
        }
    }
    file.close();
    temp.close();
    remove(dbPath.c_str());
    rename(tmpPath.c_str(), dbPath.c_str());

    if (!found)
        cout << "⚠  Key ID not found in the system." << endl;
}

void KeycardManager::expireOldKeycards() const {
    ifstream file(dbPath);
    string tmpPath = dbPath + ".tmp";
    ofstream temp(tmpPath);

    if (!file || !temp) {
        cerr << "[ERROR] Unable to access keycard database!" << endl;
        return;
    }

    string name, key, timeIssued;
    bool valid;
    bool updated = false;
    time_t now   = time(0);
    int expiredCount = 0;

    while (file >> name >> key >> valid) {
        getline(file, timeIssued);
        tm tmIssueTime = {};
        istringstream ss(timeIssued);
        ss >> get_time(&tmIssueTime, " %a %b %d %H:%M:%S %Y");

        if (!ss.fail()) {
            time_t issueTime = mktime(&tmIssueTime);
            if (valid && difftime(now, issueTime) > 86400) {
                valid = false;
                updated = true;
                expiredCount++;
            }
        }
        temp << name << " " << key << " " << valid << " " << timeIssued << "\n";
    }
    file.close();
    temp.close();
    remove(dbPath.c_str());
    rename(tmpPath.c_str(), dbPath.c_str());

    if (updated)
        cout << "✓ Expired " << expiredCount << " old keycard(s) (>24h)." << endl;
    else
        cout << "✓ No keycards needed expiration." << endl;
}

void KeycardManager::listAllKeycards() const {
    ifstream file(dbPath);
    if (!file) {
        cout << "⚠  No keycard database found or it is empty." << endl;
        return;
    }

    cout << "\n┌──────────────┬──────────────────────┬────────┬──────────────────────────────┐" << endl;
    cout << "│  Guest Name  │       Key ID         │ Status │       Issue Time             │" << endl;
    cout << "├──────────────┼──────────────────────┼────────┼──────────────────────────────┤" << endl;

    string name, key, timeIssued;
    bool valid;
    int count = 0;
    while (file >> name >> key >> valid) {
        getline(file, timeIssued);
        string status = valid ? "ACTIVE" : "EXPIRED";
        cout << "│ " << left << setw(12) << name
             << " │ " << setw(20) << key
             << " │ " << setw(6)  << status
             << " │ " << setw(28) << timeIssued << " │" << endl;
        count++;
    }
    cout << "└──────────────┴──────────────────────┴────────┴──────────────────────────────┘" << endl;
    cout << "Total keycards: " << count << endl;
}
