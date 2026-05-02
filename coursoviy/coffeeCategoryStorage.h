#pragma once
#include "coffeeCategory.h"

class CoffeeCategoryStorage {
public:
    explicit CoffeeCategoryStorage(int maxCount);
    ~CoffeeCategoryStorage();

    bool saveToFile(const char* fileName) const;
    bool loadFromFile(const char* fileName);
    bool saveToTwoFiles(const char* mainFile, const char* backupFile) const;
    bool loadFromAnyFile(const char* mainFile, const char* backupFile);

    bool addCategory(const CoffeeCategory& category);
    int findById(int id) const;
    bool removeById(int id);
    void printAll() const;

    int getCount() const;

private:
    CoffeeCategory* arr_;
    int maxCount_;
    int count_;
};
