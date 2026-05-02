#pragma once
#include "user.h"

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

    int getCount() const;

private:
    User* arr_;
    int maxCount_;
    int count_;
};