#pragma once

#include "coffee.h"
#include "myTest.h"
#include "coffeeCategory.h"
#include "coffeeSelector.h"
#include "resultTest.h"
#include "user.h"

class CoffeeCategoryStorage;

class CoffeeStorage {
public:
    explicit CoffeeStorage(int maxCount);
    ~CoffeeStorage();

    bool saveToFile(const char* fileName) const;
    bool loadFromFile(const char* fileName);
    bool saveToTwoFiles(const char* mainFile, const char* backupFile) const;
    bool loadFromAnyFile(const char* mainFile, const char* backupFile);

    bool addCoffee(const Coffee& coffee);
    void loadDefaultsIfEmpty();
    int findById(int id) const;
    const Coffee* getByIndex(int index) const;
    int findByNameContains(const char* query, int indexes[], int maxResults) const;
    bool removeCoffeeById(int id);
    bool searchAndPrintByName(const char* query) const;
    bool searchAndPrintByName(const char* query, const CoffeeCategoryStorage& categoryStorage) const;
    void printAll() const;
    void printAll(const CoffeeCategoryStorage& categoryStorage) const;

    int getCount() const;

private:
    Coffee* arr_;
    int maxCount_;
    int count_;
};

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

class CoffeeCategoryStorage {
public:
    explicit CoffeeCategoryStorage(int maxCount);
    ~CoffeeCategoryStorage();

    bool saveToFile(const char* fileName) const;
    bool loadFromFile(const char* fileName);
    bool saveToTwoFiles(const char* mainFile, const char* backupFile) const;
    bool loadFromAnyFile(const char* mainFile, const char* backupFile);

    bool addCategory(const CoffeeCategory& category);
    void loadDefaultsIfEmpty();
    int findById(int id) const;
    const CoffeeCategory* getById(int id) const;
    const char* getNameById(int id) const;
    bool removeById(int id);
    void printAll() const;

    int getCount() const;

private:
    CoffeeCategory* arr_;
    int maxCount_;
    int count_;
};

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

class ResultStorage {
public:
    explicit ResultStorage(int maxCount);
    ~ResultStorage();

    bool saveToFile(const char* fileName) const;
    bool loadFromFile(const char* fileName);
    bool saveToTwoFiles(const char* mainFile, const char* backupFile) const;
    bool loadFromAnyFile(const char* mainFile, const char* backupFile);

    bool addResult(const Result& result);
    int getNextAttemptIdForUser(int userId) const;
    bool addAnswerForUserAttempt(int userId, int attemptId, int questionId, char choice);
    void printHistoryForUser(int userId) const;

    int findByQuestionId(int questionId) const;
    bool removeByQuestionId(int questionId);
    void printAll() const;
    const Result* data() const;

    int getCount() const;

private:
    Result* arr_;
    int maxCount_;
    int count_;
};

class UserStorage {
public:
    explicit UserStorage(int maxCount);
    ~UserStorage();

    bool saveToFile(const char* fileName) const;
    bool loadFromFile(const char* fileName);
    bool loadFromAnyFile(const char* mainFile, const char* backupFile);
    bool saveToTwoFiles(const char* mainFile, const char* backupFile) const;

    int findByLogin(const char* login) const;
    bool registerUser(const User& user);
    bool loginUser(const char* login, const char* password, User& foundUser) const;
    bool updateUser(const User& user);
    void printCurrentUserHistory() const;

    int getCount() const;

private:
    User* arr_;
    int maxCount_;
    int count_;
};
