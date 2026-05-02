#include "coffeeCategoryStorage.h"
#include <fstream>
#include <iostream>

CoffeeCategoryStorage::CoffeeCategoryStorage(int maxCount) : arr_(nullptr), maxCount_(maxCount), count_(0) {
    if (maxCount_ > 0) arr_ = new CoffeeCategory[maxCount_];
    else maxCount_ = 0;
}

CoffeeCategoryStorage::~CoffeeCategoryStorage() { delete[] arr_; }

bool CoffeeCategoryStorage::saveToFile(const char* fileName) const {
    if (!fileName || !arr_ || count_ < 0) return false;
    std::ofstream out(fileName, std::ios::binary);
    if (!out.is_open()) return false;
    out.write(reinterpret_cast<const char*>(&count_), sizeof(count_));
    if (!out.good()) return false;
    for (int i = 0; i < count_; ++i) if (!arr_[i].writeToFile(out)) return false;
    return true;
}

bool CoffeeCategoryStorage::loadFromFile(const char* fileName) {
    count_ = 0;
    if (!fileName || !arr_ || maxCount_ <= 0) return false;
    std::ifstream in(fileName, std::ios::binary);
    if (!in.is_open()) return false;
    int countInFile = 0;
    in.read(reinterpret_cast<char*>(&countInFile), sizeof(countInFile));
    if (!in.good() || countInFile < 0 || countInFile > maxCount_) return false;
    for (int i = 0; i < countInFile; ++i) if (!arr_[i].readFromFile(in)) return false;
    count_ = countInFile;
    return true;
}

bool CoffeeCategoryStorage::saveToTwoFiles(const char* mainFile, const char* backupFile) const { return saveToFile(mainFile) && saveToFile(backupFile); }

bool CoffeeCategoryStorage::loadFromAnyFile(const char* mainFile, const char* backupFile) {
    if (loadFromFile(mainFile)) return true;
    return loadFromFile(backupFile);
}

bool CoffeeCategoryStorage::addCategory(const CoffeeCategory& category) {
    if (!arr_ || maxCount_ <= 0 || count_ < 0 || count_ >= maxCount_) return false;
    arr_[count_++] = category;
    return true;
}

int CoffeeCategoryStorage::findById(int id) const {
    if (!arr_ || count_ <= 0) return -1;
    for (int i = 0; i < count_; ++i) if (arr_[i].getId() == id) return i;
    return -1;
}

bool CoffeeCategoryStorage::removeById(int id) {
    if (!arr_ || count_ <= 0) return false;
    int pos = findById(id);
    if (pos == -1) return false;
    for (int i = pos; i < count_ - 1; ++i) arr_[i] = arr_[i + 1];
    --count_;
    return true;
}

void CoffeeCategoryStorage::printAll() const {
    if (!arr_ || count_ <= 0) { std::cout << "No category data\n"; return; }
    for (int i = 0; i < count_; ++i) { arr_[i].show(); std::cout << "----------------\n"; }
}

int CoffeeCategoryStorage::getCount() const { return count_; }
