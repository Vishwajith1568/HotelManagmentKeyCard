#include "../include/Keycard.h"
#include "../include/KeycardManager.h"
#include "../include/Utils.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

void printBanner() {
    cout << "\n╔══════════════════════════════════════════════╗" << endl;
    cout << "║    🏨  Hotel Keycard Access Control System   ║" << endl;
    cout << "║         Simulated RFID-Based Security        ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;
}

void printMenu() {
    cout << "\n┌─────────────────────────────┐" << endl;
    cout << "│        MAIN MENU            │" << endl;
    cout << "├─────────────────────────────┤" << endl;
    cout << "│  1. Generate New Keycard    │" << endl;
    cout << "│  2. Validate Keycard        │" << endl;
    cout << "│  3. Invalidate Keycard      │" << endl;
    cout << "│  4. Admin Override / Reset  │" << endl;
    cout << "│  5. Auto-Expire Old Keys    │" << endl;
    cout << "│  6. List All Keycards       │" << endl;
    cout << "│  7. Exit                    │" << endl;
    cout << "└─────────────────────────────┘" << endl;
    cout << "Enter choice: ";
}

int main() {
    KeycardManager manager("data/keycards.txt");
    int choice;
    string guestName, enteredKey;

    printBanner();
    cout << "\nInitializing keycard system..." << endl;

    while (true) {
        printMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Enter Guest Name: ";
                cin >> guestName;
                manager.generateKeycard(guestName);
                break;

            case 2:
                cout << "Enter Key ID to Validate: ";
                cin >> enteredKey;
                manager.validateKeycard(enteredKey);
                break;

            case 3:
                cout << "Enter Key ID to Invalidate: ";
                cin >> enteredKey;
                manager.invalidateKeycard(enteredKey);
                break;

            case 4:
                manager.adminOverride();
                break;

            case 5:
                manager.expireOldKeycards();
                break;

            case 6:
                manager.listAllKeycards();
                break;

            case 7:
                cout << "\n✓ System shutdown complete. Goodbye!\n" << endl;
                return 0;

            default:
                cout << "Invalid choice! Please select 1–7." << endl;
        }
    }
}
