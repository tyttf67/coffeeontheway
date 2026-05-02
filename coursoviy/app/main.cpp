#include <iostream>
#include "consoleApp.h"
#include "storage.h"






int main() {

    const int MAX = 10;

    CoffeeStorage coffeeStorage(MAX);
    TestStorage testStorage(MAX);
    CoffeeCategoryStorage categoryStorage(MAX);
    CoffeeSelectorStorage selectorStorage(MAX);
    ResultStorage resultStorage(MAX);
    UserStorage userStorage(MAX);



    coffeeStorage.loadFromAnyFile("coffee.dat", "coffee_backup.dat");
    testStorage.loadFromAnyFile("myTest.dat", "myTest_backup.dat");
    categoryStorage.loadFromAnyFile("coffeeCategory.dat", "coffeeCategory_backup.dat");
    selectorStorage.loadFromAnyFile("coffeeSelector.dat", "coffeeSelector_backup.dat");
    resultStorage.loadFromFile("resultTest.dat");

    userStorage.loadFromFile("user.dat");

    
    {
        ConsoleApp app(
            coffeeStorage,
            testStorage,
            categoryStorage,
            selectorStorage,
            resultStorage,
            userStorage
        );

        app.run();  
    }
    //зберігати дані тесту щоб  потому відображати в профілі в  меню
  
    coffeeStorage.saveToTwoFiles("coffee.dat", "coffee_backup.dat");
    testStorage.saveToTwoFiles("myTest.dat", "myTest_backup.dat");
    categoryStorage.saveToTwoFiles("coffeeCategory.dat", "coffeeCategory_backup.dat");
    selectorStorage.saveToTwoFiles("coffeeSelector.dat", "coffeeSelector_backup.dat");
    resultStorage.saveToFile("resultTest.dat");

    userStorage.saveToTwoFiles("user.dat");

    std::cout << "Saved successfully!\n";

    return 0;
}
