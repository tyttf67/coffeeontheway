#include "storage.h"
#include <fstream>
#include <iostream>
#include <cstring>

CoffeeSelectorStorage::CoffeeSelectorStorage(int maxCount) : arr_(nullptr), maxCount_(maxCount), count_(0) {
    if (maxCount_ > 0) arr_ = new CoffeeSelector[maxCount_];
    else maxCount_ = 0;
}

CoffeeSelectorStorage::~CoffeeSelectorStorage() { delete[] arr_; }

bool CoffeeSelectorStorage::saveToFile(const char* fileName) const {
    if (!fileName || !arr_) return false;
    std::ofstream out(fileName, std::ios::binary);
    if (!out.is_open()) return false;
    out.write(reinterpret_cast<const char*>(&count_), sizeof(count_));
    if (!out.good()) return false;
    for (int i = 0; i < count_; ++i) { out.write(reinterpret_cast<const char*>(&arr_[i]), sizeof(CoffeeSelector)); if (!out.good()) return false; }
    return true;
}

bool CoffeeSelectorStorage::loadFromFile(const char* fileName) {
    count_ = 0;
    if (!fileName || !arr_ || maxCount_ <= 0) return false;
    std::ifstream in(fileName, std::ios::binary);
    if (!in.is_open()) return false;
    int countInFile = 0;
    in.read(reinterpret_cast<char*>(&countInFile), sizeof(countInFile));
    if (!in.good() || countInFile < 0 || countInFile > maxCount_) return false;
    for (int i = 0; i < countInFile; ++i) { in.read(reinterpret_cast<char*>(&arr_[i]), sizeof(CoffeeSelector)); if (!in.good()) return false; }
    count_ = countInFile;
    return true;
}

bool CoffeeSelectorStorage::saveToTwoFiles(const char* mainFile, const char* backupFile) const { return saveToFile(mainFile) && saveToFile(backupFile); }
bool CoffeeSelectorStorage::loadFromAnyFile(const char* mainFile, const char* backupFile) { return loadFromFile(mainFile) || loadFromFile(backupFile); }

int CoffeeSelectorStorage::findByNameContains(const char* query) const {
    if (arr_ == nullptr || query == nullptr || query[0] == '\0' || count_ <= 0) return -1;
    return -1;
}

bool CoffeeSelectorStorage::addSelector(const CoffeeSelector& selector) { if (!arr_ || count_ < 0 || count_ >= maxCount_) return false; arr_[count_++] = selector; return true; }
int CoffeeSelectorStorage::findByIndex(int index) const { if (count_ <= 0 || index < 0 || index >= count_) return -1; return index; }
bool CoffeeSelectorStorage::updateSelector(int index, const CoffeeSelector& selector) { int pos = findByIndex(index); if (pos == -1) return false; arr_[pos] = selector; return true; }
bool CoffeeSelectorStorage::removeByIndex(int index) { if (!arr_ || count_ <= 0 || index < 0 || index >= count_) return false; for (int i = index; i < count_ - 1; ++i) arr_[i] = arr_[i + 1]; --count_; return true; }
void CoffeeSelectorStorage::printAll() const { if (!arr_ || count_ <= 0) { std::cout << "No selector data to print.\n"; return; } for (int i = 0; i < count_; ++i) { std::cout << "CoffeeSelector #" << i << '\n'; std::cout << "-------------------------\n"; } }
int CoffeeSelectorStorage::getCount() const { return count_; }
