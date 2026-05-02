#pragma once
#include "coffee.h"

class CoffeeStorage {
public:
    explicit CoffeeStorage(int maxCount);
    ~CoffeeStorage();

    bool saveToFile(const char* fileName) const;
    bool loadFromFile(const char* fileName);
    bool saveToTwoFiles(const char* mainFile, const char* backupFile) const;
    bool loadFromAnyFile(const char* mainFile, const char* backupFile);

    bool addCoffee(const Coffee& coffee);
    int findById(int id) const;
    bool removeCoffeeById(int id);
    void printAll() const;

    int getCount() const;

private:
    Coffee* arr_;
    int maxCount_;
    int count_;
};
