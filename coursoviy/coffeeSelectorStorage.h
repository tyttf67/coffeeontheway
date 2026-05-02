#pragma once
#include "coffeeSelector.h"

class CoffeeSelectorStorage {
public:
    explicit CoffeeSelectorStorage(int maxCount);
    ~CoffeeSelectorStorage();

    bool saveToFile(const char* fileName) const;
    bool loadFromFile(const char* fileName);
    bool saveToTwoFiles(const char* mainFile, const char* backupFile) const;
    bool loadFromAnyFile(const char* mainFile, const char* backupFile);

    int findByNameContains(const char* query) const;
    bool addSelector(const CoffeeSelector& selector);
    int findByIndex(int index) const;
    bool removeByIndex(int index);
    void printAll() const;

    int getCount() const;

private:
    CoffeeSelector* arr_;
    int maxCount_;
    int count_;
};
