#include "consoleApp.h"

#include <iostream>
#include <limits>

ConsoleApp::ConsoleApp(
    CoffeeStorage& coffeeStorage,
    TestStorage& testStorage,
    CoffeeCategoryStorage& categoryStorage,
    CoffeeSelectorStorage& selectorStorage,
    ResultStorage& resultStorage,
    UserStorage& userStorage
) : coffeeStorage(coffeeStorage),
    testStorage(testStorage),
    categoryStorage(categoryStorage),
    selectorStorage(selectorStorage),
    resultStorage(resultStorage),
    userStorage(userStorage),
    currentUser(),
    isLoggedIn(false) {
}

void ConsoleApp::run() {
    while (true) {
        std::cout << "\n=== MENU ===\n";
        std::cout << "1. List coffee cards\n";
        std::cout << "2. Open coffee card by ID\n";
        std::cout << "3. Search coffee card\n";
        std::cout << "4. Register user\n";
        std::cout << "5. Login\n";
        std::cout << "6. Start test\n";
        std::cout << "7. Show current user\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";

        int choice = -1;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0) {
            break;
        } else if (choice == 1) {
            selector.printCoffeeCards();
        } else if (choice == 2) {
            int id = 0;
            std::cout << "Enter ID: ";
            if (!(std::cin >> id)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (!selector.showCoffeeCardById(id)) {
                std::cout << "Card not found.\n";
            }
        } else if (choice == 3) {
            char query[128];
            std::cout << "Enter search text: ";
            std::cin.getline(query, sizeof(query));

            if (!coffeeStorage.searchAndPrintByName(query)) {
                std::cout << "No cards found.\n";
            }
        } else if (choice == 4) {
            char name[100];
            char gmail[100];
            char login[64];
            char password[64];
            char favouriteDrinks[100];

            std::cout << "Name: ";
            std::cin.getline(name, sizeof(name));
            std::cout << "Gmail: ";
            std::cin.getline(gmail, sizeof(gmail));
            std::cout << "Login: ";
            std::cin.getline(login, sizeof(login));
            std::cout << "Password: ";
            std::cin.getline(password, sizeof(password));
            std::cout << "Favourite drinks (comma-separated): ";
            std::cin.getline(favouriteDrinks, sizeof(favouriteDrinks));

            const int newUserId = userStorage.getCount() + 1;
            User newUser(newUserId, name, login, gmail, password, favouriteDrinks);

            if (userStorage.registerUser(newUser)) {
                std::cout << "User registered and saved in storage.\n";
            } else {
                std::cout << "Registration failed (login may already exist or storage is full).\n";
            }
        } else if (choice == 5) {
            char inLogin[64];
            char inPass[64];
            std::cout << "Login: ";
            std::cin.getline(inLogin, sizeof(inLogin));
            std::cout << "Password: ";
            std::cin.getline(inPass, sizeof(inPass));

            User foundUser;
            if (userStorage.loginUser(inLogin, inPass, foundUser)) {
                currentUser = foundUser;
                isLoggedIn = true;
                std::cout << "Logged in successfully.\n";
            } else {
                isLoggedIn = false;
                std::cout << "Wrong login/password.\n";
            }
        } else if (choice == 6) {
            if (!isLoggedIn) {
                std::cout << "Login first.\n";
                continue;
            }
            selector.run();
        } else if (choice == 7) {
            if (!isLoggedIn) {
                std::cout << "No active user session. Login first.\n";
                continue;
            }
            currentUser.show();
        } else {
            std::cout << "Unknown menu item.\n";
        }
    }
}
