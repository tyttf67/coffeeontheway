#include "consoleApp.h"

#include <iostream>
#include <limits>
#include <cctype>

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
//прибрати ці фкції з класу, бо вони не використовуються в консолі 
void ConsoleApp::runAndSaveTestForCurrentUser() {
    const int userId = currentUser.getId();

    const int newAttemptId = resultStorage.getNextAttemptIdForUser(userId);

    int testCount = 0;
    const Test* tests = getDefaultTests(testCount);

    std::cout << "\n=== Test (Attempt #" << newAttemptId << ") ===\n";
    for (int i = 0; i < testCount; ++i) {
        tests[i].show();

        char answer = 0;
        while (true) {
            std::cout << "Your answer (A/B/C): ";
            if (!(std::cin >> answer)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            answer = static_cast<char>(std::toupper(static_cast<unsigned char>(answer)));
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (tests[i].getCoffeeIndexForChoice(answer) != -1) {
                break;
            }
            std::cout << "Please enter only A, B, or C.\n";
        }

        if (!resultStorage.addAnswerForUserAttempt(userId, newAttemptId, tests[i].getId(), answer)) {
            std::cout << "Cannot save result (result storage is full).\n";
            return;
        }

        std::cout << "-------------------------\n";
    }

    std::cout << "Test completed and saved to history.\n";
}

void ConsoleApp::printCurrentUserHistory() const {
    resultStorage.printHistoryForUser(currentUser.getId());
}

void ConsoleApp::run() {
    while (true) {
        std::cout << "\n=== MENU ===\n";
        std::cout << "1. List coffee cards\n";
        std::cout << "2. Search coffee card\n";
        std::cout << "3. Register user\n";
        std::cout << "4. Login\n";
        std::cout << "5. Start test\n";
        std::cout << "6. Show user\n";
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
            selector.printCoffeeCards(categoryStorage);
        } else if (choice == 2) {

            char query[128];
            std::cout << "Enter search text: ";
            std::cin.getline(query, sizeof(query));

            if (!coffeeStorage.searchAndPrintByName(query, categoryStorage)) {
                std::cout << "No cards found.\n";
            }

        } else if (choice == 3) {

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
            }
            else {
                std::cout << "Registration failed (login may already exist or storage is full).\n";
            }



            
        } else if (choice == 4) {


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
            }
            else {
                isLoggedIn = false;
                std::cout << "Wrong login/password.\n";
            }

        } else if (choice == 5) {
            
            if (!isLoggedIn) {
                std::cout << "Login first.\n";
                continue;
            }
            runAndSaveTestForCurrentUser();

        } else if (choice == 6) {
            
            if (!isLoggedIn) {
                std::cout << "No active user session. Login first.\n";
                continue;
            }
            currentUser.show();
            printCurrentUserHistory();            
        } else {
            std::cout << "Unknown menu item.\n";
        }
    }
}

