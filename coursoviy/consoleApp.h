#pragma once

#include "storage.h"
#include "coffeeSelector.h"

class ConsoleApp {
private:
    CoffeeStorage& coffeeStorage;
    TestStorage& testStorage;
    CoffeeCategoryStorage& categoryStorage;
    CoffeeSelectorStorage& selectorStorage;
    ResultStorage& resultStorage;

    UserStorage& userStorage;
    User currentUser;
    bool isLoggedIn;
    CoffeeSelector selector;
    
    void runAndSaveTestForCurrentUser();
    void printCurrentUserHistory() const;
    

public:
    ConsoleApp(
        CoffeeStorage& coffeeStorage,
        TestStorage& testStorage,
        CoffeeCategoryStorage& categoryStorage,
        CoffeeSelectorStorage& selectorStorage,
        ResultStorage& resultStorage,
        UserStorage& userStorage
    );

    void run();
};
