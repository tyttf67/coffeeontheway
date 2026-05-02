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
    CoffeeSelector selector;

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
