#pragma once

#include "coffeeStorage.h"
#include "myTestStorage.h"
#include "coffeeCategoryStorage.h"
#include "coffeeSelectorStorage.h"
#include "resultTestStorage.h"
#include "user.h"
#include "coffeeSelector.h"

class ConsoleApp {
private:
    CoffeeStorage& coffeeStorage;
    TestStorage& testStorage;
    CoffeeCategoryStorage& categoryStorage;
    CoffeeSelectorStorage& selectorStorage;
    ResultStorage& resultStorage;

    User& user;
    CoffeeSelector selector;

public:
    ConsoleApp(
        CoffeeStorage& coffeeStorage,
        TestStorage& testStorage,
        CoffeeCategoryStorage& categoryStorage,
        CoffeeSelectorStorage& selectorStorage,
        ResultStorage& resultStorage,
        User& user
    );

    void run();
};