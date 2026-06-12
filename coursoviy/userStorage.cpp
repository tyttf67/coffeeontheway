#include "storage.h"
#include <fstream>
#include <cstring>
#include <functional>
#include <string>    // ← додай це


std::string hashPassword(const std::string& pass) {
    return std::to_string(std::hash<std::string>{}(pass));
}

UserStorage::UserStorage(int maxCount)
    : arr_(nullptr), maxCount_(maxCount), count_(0) {
    if (maxCount_ > 0) {
        arr_ = new User[maxCount_];
    } else {
        maxCount_ = 0;
    }
}

UserStorage::~UserStorage() {
    delete[] arr_;
}

bool UserStorage::saveToFile(const char* fileName) const {
    if (!fileName || !arr_) return false;

    std::ofstream out(fileName, std::ios::binary);
    if (!out.is_open()) return false;

    out.write(reinterpret_cast<const char*>(&count_), sizeof(count_));
    if (!out.good()) return false;

    for (int i = 0; i < count_; ++i) {
        const User& u = arr_[i];
        int id = u.getId();

        out.write(reinterpret_cast<const char*>(&id), sizeof(id));
        out.write(u.getName(), sizeof(char) * 100);
        out.write(u.getLogin(), sizeof(char) * 64);
        out.write(u.getPassword(), sizeof(char) * 64);
        out.write(u.getGmail(), sizeof(char) * 100);
        out.write(u.getFavouriteDrinks(), sizeof(char) * 1024);

        if (!out.good()) return false;
    }

    return true;
}

bool UserStorage::loadFromFile(const char* fileName) {
    count_ = 0;
    if (!fileName || !arr_ || maxCount_ <= 0) return false;

    std::ifstream in(fileName, std::ios::binary);
    if (!in.is_open()) return false;

    int fileCount = 0;
    in.read(reinterpret_cast<char*>(&fileCount), sizeof(fileCount));
    if (!in.good() || fileCount < 0 || fileCount > maxCount_) return false;

    count_ = fileCount;

    for (int i = 0; i < count_; ++i) {
        int id;
        char name[100];
        char login[64];
        char password[64];
        char gmail[100];
        char drinks[1024];

        in.read(reinterpret_cast<char*>(&id), sizeof(id));
        in.read(name, sizeof(name));
        in.read(login, sizeof(login));
        in.read(password, sizeof(password));
        in.read(gmail, sizeof(gmail));
        in.read(drinks, sizeof(drinks));

        if (!in.good()) return false;

        name[sizeof(name) - 1] = '\0';
        login[sizeof(login) - 1] = '\0';
        password[sizeof(password) - 1] = '\0';
        gmail[sizeof(gmail) - 1] = '\0';
        drinks[sizeof(drinks) - 1] = '\0';

        arr_[i].setProfile(id, name, login, gmail, password, drinks);
    }

    return true;
}

bool UserStorage::loadFromAnyFile(const char* mainFile, const char* backupFile) {
    if (loadFromFile(mainFile)) return true;
    return loadFromFile(backupFile);
}

bool UserStorage::saveToTwoFiles(const char* mainFile, const char* backupFile) const {
    return saveToFile(mainFile) && saveToFile(backupFile);
}

int UserStorage::findByLogin(const char* login) const {
    if (!arr_ || !login) return -1;

    for (int i = 0; i < count_; ++i) {
        if (std::strcmp(arr_[i].getLogin(), login) == 0) return i;
    }

    return -1;
}

bool UserStorage::registerUser(const User& user) {
    if (!arr_ || count_ < 0 || count_ >= maxCount_) return false;
    if (findByLogin(user.getLogin()) != -1) return false;

    arr_[count_] = user;
    ++count_;
    return true;
}

bool UserStorage::loginUser(const char* login, const char* password, User& foundUser) const {
    const int pos = findByLogin(login);
    if (pos == -1) return false;

    if (std::strcmp(arr_[pos].getPassword(), password) != 0) return false;

    foundUser = arr_[pos];
    return true;
}

bool UserStorage::updateUser(const User& user) {   // оновлення користувача по айді
    if (!arr_) return false;

    for (int i = 0; i < count_; ++i) {
        if (arr_[i].getId() == user.getId()) {
            arr_[i] = user;
            return true;
        }
    }

    return false;
}

bool UserStorage::addFavouriteDrinkForUser(int userId, const char* drinkName, User& updatedUser) {
    if (!arr_ || !drinkName || drinkName[0] == '\0') return false;

    for (int i = 0; i < count_; ++i) {
        if (arr_[i].getId() == userId) {
            if (!arr_[i].addFavouriteDrink(drinkName)) {
                return false;
            }
            updatedUser = arr_[i];
            return true;
        }
    }

    return false;
}

bool UserStorage::removeById(int id) {
    if (!arr_ || count_ <= 0) return false;

    for (int i = 0; i < count_; ++i) {
        if (arr_[i].getId() == id) {
            for (int j = i; j < count_ - 1; ++j) {
                arr_[j] = arr_[j + 1];
            }
            --count_;
            return true;
        }
    }

    return false;
}

bool UserStorage::removeByLogin(const char* login) {
    int pos = findByLogin(login);
    if (pos == -1) return false;
    return removeById(arr_[pos].getId());
}



int UserStorage::getCount() const {
    return count_;
}
