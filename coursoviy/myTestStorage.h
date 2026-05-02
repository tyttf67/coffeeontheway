#pragma once
#include "myTest.h"

class TestStorage {
public:
    explicit TestStorage(int maxCount);
    ~TestStorage();

    bool saveToFile(const char* fileName) const;
    bool loadFromFile(const char* fileName);
    bool saveToTwoFiles(const char* mainFile, const char* backupFile) const;
    bool loadFromAnyFile(const char* mainFile, const char* backupFile);

    bool addTest(const Test& test);
    int findById(int id) const;
    bool removeById(int id);
    void printAll() const;

    int getCount() const;

private:
    Test* arr_;
    int maxCount_;
    int count_;
};
