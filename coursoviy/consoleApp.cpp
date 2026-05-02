#include <iostream> 
#include "coffee.h"
#include <limits>
#include "coffeeSelector.h"
#include "coffee.h"
#include "coffeeCategory.h"
#include "myTest.h"
#include "user.h"

int main(){

    CoffeeSelector selector;
    User user;
    Coffee coffee;
    CoffeeCategory coffeeCategory;
    Test myTest;
    Result resultTest;


while (true) {
    std::cout << "\n=== MENU ===\n";
    std::cout << "1. List coffee cards\n";
    std::cout << "2. Open coffee card by ID\n";
    std::cout << "3. Search coffee card\n";
    std::cout << "4. Register/Update user\n";
    std::cout << "5. Verify user\n";
    std::cout << "6. Start test\n";
    std::cout << "7. Show user\n";
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
    }
    else if (choice == 1) {
        selector.printCoffeeCards();
    }
    else if (choice == 2) {
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
    }
    else if (choice == 3) {
        char query[128];
        std::cout << "Enter search text: ";
        std::cin.getline(query, sizeof(query));

        if (!selector.searchCoffeeCards(query)) {
            std::cout << "No cards found.\n";
        }
    }
    else if (choice == 4) {
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

        user.setProfile(1, name, login, gmail, password, favouriteDrinks);
        std::cout << "User profile saved.\n";
    }
    else if (choice == 5) {
        if (!user.hasCredentials()) {
            std::cout << "Register user first (menu item 4).\n";
            continue;
        }

        char inLogin[64], inPass[64];
        std::cout << "Login: ";
        std::cin.getline(inLogin, sizeof(inLogin));
        std::cout << "Password: ";
        std::cin.getline(inPass, sizeof(inPass));

        if (user.verify(inLogin, inPass)) {
            std::cout << "Verified.\n";
        }
        else {
            std::cout << "Wrong login/password.\n";
        }
    }
    else if (choice == 6) {
        if (!user.isVerified()) {
            std::cout << "Verify user first.\n";
            continue;
        }
        selector.run();
    }
    else if (choice == 7) {
        user.show();
        std::cout << "Your tests  sproby: ";
        resultTest.getAttemptId();
    }
    else {
        std::cout << "Unknown menu item.\n";
    }
}}