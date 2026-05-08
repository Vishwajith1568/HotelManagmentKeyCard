<div align="center">

```
╔══════════════════════════════════════════════════════════════╗
║                                                              ║
║    🏨   H O T E L   K E Y C A R D   S Y S T E M   🔐       ║
║         Simulated Digital Access Control in C++              ║
║                                                              ║
╚══════════════════════════════════════════════════════════════╝
```

![C++](https://img.shields.io/badge/C++-17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows%20%7C%20macOS-lightgrey?style=for-the-badge)
![Build](https://img.shields.io/badge/Build-Makefile-green?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Active-brightgreen?style=for-the-badge)

*A secure, RFID-inspired keycard access control system simulated in C++*

</div>

---

## 📖 Overview

The **Hotel Keycard & Access Control System** is a C++ application that simulates an RFID-based digital keycard management system — the kind found in real hotels and secure facilities. It models the full lifecycle of a keycard: **generation, validation, expiration, and admin override**.

This project emphasizes **security concepts over typical booking or payment workflows**, demonstrating:

- Unique key generation via **polynomial rolling hash**
- Persistent storage with **flat-file database** management
- **Multi-level access control** (guest vs. admin)
- **Automatic expiration** of keys older than 24 hours
- Safe **atomic file writes** (write-to-temp → rename pattern)

> 📌 Built as a group project to demonstrate how digital keycard systems can be **secure, scalable, and effective** in IoT-based authentication scenarios.

---

## 👥 Group Members

| Roll Number   | Name               |
|---------------|--------------------|
| 23211A3203    | Vishwajith Teja .A |
| 23211A3207    | Rakesh .B          |
| 23211A3244    | P. Pavan           |
| 23211A3248    | S. Venkat Sai      |

---

## ✨ Features

| Feature | Description |
|---------|-------------|
| 🔑 **Key Generation** | Creates a unique hashed keycard ID for each guest on check-in |
| ✅ **Key Validation** | Simulates card scan — grants or denies room access |
| 🚫 **Key Invalidation** | Deactivates a keycard on checkout or loss |
| 🛡️ **Admin Override** | Resets a key to a new guest without deleting history |
| ⏰ **Auto-Expiry** | Automatically expires keys older than 24 hours |
| 📋 **List All Keys** | Displays all keycards in a formatted table |
| 💾 **Persistent Storage** | All records survive program restarts via file I/O |

---

## 🗂️ Project Structure

```
HotelManagmentKeyCard/
│
├── 📁 src/                     # Source files
│   ├── Hotel.cpp               # Main entry point & menu loop
│   ├── Keycard.cpp             # Keycard class implementation
│   ├── KeycardManager.cpp      # Core CRUD operations on keycards
│   └── Utils.cpp               # Hashing, time formatting utilities
│
├── 📁 include/                 # Header files
│   ├── Keycard.h               # Keycard class declaration
│   ├── KeycardManager.h        # KeycardManager class declaration
│   └── Utils.h                 # Utility function declarations
│
├── 📁 tests/                   # Test scripts
│   └── smoke_test.sh           # Automated smoke test (bash)
│
├── 📁 data/                    # Runtime data (git-ignored)
│   └── keycards.txt            # Flat-file keycard database (auto-created)
│
├── 📁 build/                   # Compiled object files & binary (git-ignored)
│
├── 📄 Makefile                 # Build system
├── 📄 .gitignore               # Git exclusions
└── 📄 README.md                # This file
```

---

## ⚙️ How It Works

### Key Generation
```
Guest Name  ──►  Random 6-digit string  ──►  Polynomial Hash  ──►  Key ID
                  e.g. "482910"               hash(s) = Σ(c * 31^i)   e.g. "3847291650"
```

Each keycard record stored in `data/keycards.txt`:
```
Alice  3847291650  1  Mon Apr 07 14:32:10 2025
Bob    2918374650  0  Sun Apr 06 09:15:00 2025
```
Fields: `GuestName | KeyID | IsValid(1/0) | IssueTimestamp`

### Validation Flow
```
Scan Key ID ──► Search DB ──► Found?
                                ├── Yes + Valid   ──► ✅ Access Granted
                                ├── Yes + Invalid ──► ❌ Access Denied (expired/invalidated)
                                └── No            ──► ❌ Access Denied (not found)
```

### Atomic File Write Pattern
To prevent data corruption during updates:
```
Read keycards.txt  ──►  Write changes to temp.txt  ──►  Remove original  ──►  Rename temp → keycards.txt
```

---

## 🚀 Getting Started

### Prerequisites

- **g++** with C++17 support
- **make** (GNU Make)
- Linux / macOS / Windows (with WSL or MinGW)

### Build & Run

```bash
# Clone the repository
git clone https://github.com/Vishwajith1568/HotelManagmentKeyCard.git
cd HotelManagmentKeyCard

# Build the project
make

# Run the system
make run
```

### Manual Compile (without Make)

```bash
g++ -std=c++17 -Iinclude src/Hotel.cpp src/Keycard.cpp src/KeycardManager.cpp src/Utils.cpp -o HotelKeycard
./HotelKeycard
```

---

## 🖥️ Sample Session

```
╔══════════════════════════════════════════════╗
║    🏨  Hotel Keycard Access Control System   ║
║         Simulated RFID-Based Security        ║
╚══════════════════════════════════════════════╝

┌─────────────────────────────┐
│        MAIN MENU            │
├─────────────────────────────┤
│  1. Generate New Keycard    │
│  2. Validate Keycard        │
│  3. Invalidate Keycard      │
│  4. Admin Override / Reset  │
│  5. Auto-Expire Old Keys    │
│  6. List All Keycards       │
│  7. Exit                    │
└─────────────────────────────┘
Enter choice: 1
Enter Guest Name: Alice

┌─────────────────────────────────────┐
│           KEYCARD ISSUED            │
├─────────────────────────────────────┤
│  Guest  : Alice
│  Key ID : 3847291650
│  Time   : Thu May 07 11:42:10 2025
│  Status : ACTIVE ✓                  │
└─────────────────────────────────────┘
✓ Keycard saved to database.
```

---

## 🔐 Security Design Notes

| Concept | Implementation |
|---------|---------------|
| **Key Uniqueness** | Random seed + polynomial hash ensures low collision probability |
| **Expiration** | 24-hour TTL enforced via `difftime()` on stored timestamps |
| **Invalidation** | Soft-delete (sets `isValid = 0`) preserves audit trail |
| **Admin Control** | Override replaces key ID entirely, old key becomes unreachable |
| **No Plaintext Passwords** | Keys are opaque hash strings, not guest names |

> ⚠️ **Note:** This is a simulation. For production IoT systems, replace the file DB with a proper database (SQLite/PostgreSQL), use cryptographically secure random generation (`/dev/urandom` or `std::random_device`), and enforce HTTPS/TLS on any network layer.

---

## 🧪 Running Tests

```bash
# Build first
make

# Run smoke tests
chmod +x tests/smoke_test.sh
./tests/smoke_test.sh
```

Expected output:
```
═══════════════════════════════════════
  Hotel Keycard System – Smoke Tests
═══════════════════════════════════════
  ✅  PASS: Keycard issued for Alice
  ✅  PASS: Key saved to database
  ✅  PASS: Access denied for unknown key
  ✅  PASS: Expire scan runs without crash
═══════════════════════════════════════
  Results: 4 passed, 0 failed
═══════════════════════════════════════
```

---

## 🛠️ Makefile Targets

| Command | Description |
|---------|-------------|
| `make` | Build the project |
| `make run` | Build and run the binary |
| `make clean` | Remove build artifacts and database |

---

## 🔮 Future Improvements

- [ ] Replace flat-file DB with **SQLite** for thread-safe concurrent access
- [ ] Add **AES-256 encryption** for keycard IDs at rest
- [ ] Implement **master key** / emergency override with PIN
- [ ] Add **room assignment** (keycard ↔ room number mapping)
- [ ] Web dashboard for hotel staff via **REST API** (Flask/FastAPI wrapper)
- [ ] Unit tests with **Google Test** framework

---

## 📄 License

This project is open source under the [MIT License](LICENSE).

---

<div align="center">

Made with ❤️ by Group 23211A32 — BVRIT Hyderabad

*Simulating secure access, one keycard at a time* 🔐

</div>
