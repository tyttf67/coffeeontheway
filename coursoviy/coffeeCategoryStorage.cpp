#include "storage.h"
#include <fstream>
#include <iostream>

CoffeeCategoryStorage::CoffeeCategoryStorage(int maxCount) : arr_(nullptr), maxCount_(maxCount), count_(0) {
    if (maxCount_ > 0) arr_ = new CoffeeCategory[maxCount_];
    else maxCount_ = 0;
}

CoffeeCategoryStorage::~CoffeeCategoryStorage() { delete[] arr_; }

bool CoffeeCategoryStorage::saveToFile(const char* fileName) const {
    if (!fileName || !arr_) return false;
    std::ofstream out(fileName, std::ios::binary);
    if (!out.is_open()) return false;
    out.write(reinterpret_cast<const char*>(&count_), sizeof(count_));
    if (!out.good()) return false;
    for (int i = 0; i < count_; ++i) { out.write(reinterpret_cast<const char*>(&arr_[i]), sizeof(CoffeeCategory)); if (!out.good()) return false; }
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
    for (int i = 0; i < countInFile; ++i) { in.read(reinterpret_cast<char*>(&arr_[i]), sizeof(CoffeeCategory)); if (!in.good()) return false; }
    count_ = countInFile;
    return true;
}

bool CoffeeCategoryStorage::saveToTwoFiles(const char* mainFile, const char* backupFile) const { return saveToFile(mainFile) && saveToFile(backupFile); }
bool CoffeeCategoryStorage::loadFromAnyFile(const char* mainFile, const char* backupFile) { return loadFromFile(mainFile) || loadFromFile(backupFile); }

bool CoffeeCategoryStorage::addCategory(const CoffeeCategory& category) { if (!arr_ || count_ < 0 || count_ >= maxCount_) return false; arr_[count_++] = category; return true; }
void CoffeeCategoryStorage::loadDefaultsIfEmpty() {
    if (count_ > 0) return;

    addCategory(CoffeeCategory(1, "espresso-based", "Strong coffee drinks based on espresso."));
    addCategory(CoffeeCategory(2, "milk-based", "Coffee drinks with milk or milk foam."));
    addCategory(CoffeeCategory(3, "black coffee", "Coffee drinks without milk."));
    addCategory(CoffeeCategory(4, "dessert coffee", "Sweet coffee drinks with dessert profile."));
    addCategory(CoffeeCategory(5, "cold coffee", "Cold coffee drinks with ice or cold extraction."));
    addCategory(CoffeeCategory(6, "specialty", "Special coffee dessert drinks."));
    addCategory(CoffeeCategory(7, "alternative", "Alternative brewing and extraction styles."));
}
int CoffeeCategoryStorage::findById(int id) const { if (!arr_ || count_ <= 0) return -1; for (int i = 0; i < count_; ++i) if (arr_[i].getId() == id) return i; return -1; }
const CoffeeCategory* CoffeeCategoryStorage::getById(int id) const {
    int pos = findById(id);
    if (pos == -1) return nullptr;
    return &arr_[pos];
}
const char* CoffeeCategoryStorage::getNameById(int id) const {
    const CoffeeCategory* category = getById(id);
    return category ? category->getName() : "unknown";
}
bool CoffeeCategoryStorage::updateCategory(const CoffeeCategory& category) {
    int pos = findById(category.getId());
    if (pos == -1) return false;
    arr_[pos] = category;
    return true;
}
bool CoffeeCategoryStorage::removeById(int id) { int pos = findById(id); if (pos == -1) return false; for (int i = pos; i < count_ - 1; ++i) arr_[i] = arr_[i + 1]; --count_; return true; }
void CoffeeCategoryStorage::printAll() const { if (!arr_ || count_ <= 0) { std::cout << "No category data\n"; return; } for (int i = 0; i < count_; ++i) { arr_[i].show(); std::cout << "----------------\n"; } }
int CoffeeCategoryStorage::getCount() const { return count_; }
