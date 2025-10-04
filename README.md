# Bank System (Console App) 🔵🏦

[![License](https://img.shields.io/badge/license-REPLACE%20ME-blue.svg)](LICENSE)
[![Language](https://img.shields.io/badge/language-C%2B%2B-blue.svg)](https://en.cppreference.com)
[![Issues](https://img.shields.io/github/issues/Moaaz-git/Bank-System-consoleApp?color=blue)](https://github.com/Moaaz-git/Bank-System-consoleApp/issues)
[![Repo Size](https://img.shields.io/github/repo-size/Moaaz-git/Bank-System-consoleApp?color=blue)](https://github.com/Moaaz-git/Bank-System-consoleApp)

A simple, educational console-based bank system written in C++. The application demonstrates common banking operations (account creation, authentication, deposits/withdrawals, and transaction history) using console I/O and file-based persistence. It’s intended as a learning project and a base for further enhancements.

## Features ✨

- 🔒 Secure-ish login with username/password (basic authentication for demo)
- 💳 Create and manage bank accounts
- ➕ Deposit and ➖ Withdraw funds
- 💰 Check account balance
- 📜 View transaction history
- 🗃️ Simple file-based persistence for accounts and transactions
- ✅ Basic input validation and console menus

## Installation 🛠️

Requirements
- A C++ compiler supporting C++17 or later (g++, clang, MSVC)
- Optional: make or CMake for a more reproducible build

Clone the repository
```bash
git clone https://github.com/Moaaz-git/Bank-System-consoleApp.git
cd Bank-System-consoleApp
```

Build with g++ (simple)
```bash
# If source files are at the repo root
g++ -std=c++17 -O2 -Wall -Wextra -o BankSystem *.cpp
```

Build with CMake (if you add a CMakeLists.txt)
```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

Run the app
```bash
# Unix / macOS
./BankSystem

# Windows
BankSystem.exe
```

If source files live under src/, adjust the compile command:
```bash
g++ -std=c++17 -O2 -Wall -Wextra -o BankSystem src/*.cpp
```

## Usage ▶️

When you run the program, you'll see a menu-driven interface. Use numeric selections to navigate.

Example session:
```text
                                        ______________________________________

                                                     Login Screen .
                                        ______________________________________

                                        User :
                                        Date : 4/10/2025

                                        ______________________________________

                                        Enter Username? Admin
                                        Enter Password? 82hhdb264





After Login :


                                        ______________________________________

                                                        Main Screen
                                        ______________________________________

                                        User : Admin
                                        Date : 4/10/2025

                                     ===========================================
                                                        Main Menue
                                     ===========================================
                                        [1] Show Client List.
                                        [2] Add New Client.
                                        [3] Delete Client.
                                        [4] Update Client Info.
                                        [5] Find Client.
                                        [6] Transactions.
                                        [7] Manage Users.
                                        [8] Login Registers.
                                        [9] Currency Exhange.
                                        [10] Logout.
                                     ===========================================
                                     Choose what do you want to do? [1 to 10]? 

```

Notes
- Follow on-screen prompts to perform operations.
- Data is persisted to files in the working directory (example filenames may include accounts and transactions data files). Check the repo for exact filenames used by your local build.

## Configuration ⚙️

- No environment variables required by default.
- Persistence: the app writes data files to the current working directory. Ensure the program has write permission.
- If you want to customize file paths or behavior, consider adding a configuration header (e.g., config.h) or a JSON/TOML config file and document keys here.

Suggested configuration variables (not implemented by default, add if you extend the app):
- DATA_DIR — path to store data files
- AUTO_BACKUP — enable/disable periodic backups of data files

## Contributing 🤝

Thanks for considering contributing! Suggested workflow:

1. Fork the repository and create a branch for your change:
   - git checkout -b feature/my-improvement
2. Keep changes focused and add comments where logic is non-obvious.
3. Prefer modern C++ practices (C++17+).
4. If you add new behavior, include usage examples or a small script to exercise it.
5. Open a pull request with a clear description of the change and motivation.

Please open issues for bugs or feature requests. Include steps to reproduce and expected behavior.

Code of conduct
- Be respectful and collaborative. If you want a formal CODE_OF_CONDUCT file added, please open an issue or PR.

## License

This project is licensed under [LICENSE_NAME]. See the LICENSE file for details.

(Replace [LICENSE_NAME] with a license such as MIT, Apache-2.0, or GPL-3.0 as appropriate.)

## Acknowledgments 🙏

- Educational resources and C++ tutorials that inspired the implementation.
- Open-source community examples for console apps and simple persistence.
- Special thanks to contributors, reviewers, or educators who helped shape this project.
- Special thanks to Dr. Mohammad Abu Hadhoud, owner of the Programming Advices platform  https://programmingadvices.com/

---


