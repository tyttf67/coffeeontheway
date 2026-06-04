#include "storage.h"
#include "myTest.h"
#include <fstream>
#include <iostream>


TestStorage::TestStorage(int maxCount) : arr_(nullptr), maxCount_(maxCount), count_(0) {
    if (maxCount_ > 0) arr_ = new Test[maxCount_];
    else maxCount_ = 0;
}

TestStorage::~TestStorage() { delete[] arr_; }

bool TestStorage::saveToFile(const char* fileName) const {
    if (!fileName || !arr_) return false;
    std::ofstream out(fileName, std::ios::binary);
    if (!out.is_open()) return false;
    out.write(reinterpret_cast<const char*>(&count_), sizeof(count_));
    if (!out.good()) return false;
    for (int i = 0; i < count_; ++i) {
        out.write(reinterpret_cast<const char*>(&arr_[i]), sizeof(Test));
        if (!out.good()) return false;
    }
    return true;
}

bool TestStorage::loadFromFile(const char* fileName) {
    count_ = 0;
    if (!fileName || !arr_ || maxCount_ <= 0) return false;
    std::ifstream in(fileName, std::ios::binary);
    if (!in.is_open()) return false;
    int countInFile = 0;
    in.read(reinterpret_cast<char*>(&countInFile), sizeof(countInFile));
    if (!in.good() || countInFile < 0 || countInFile > maxCount_) return false;
    for (int i = 0; i < countInFile; ++i) {
        in.read(reinterpret_cast<char*>(&arr_[i]), sizeof(Test));
        if (!in.good()) return false;
    }
    count_ = countInFile;
    return true;
}

bool TestStorage::saveToTwoFiles(const char* mainFile, const char* backupFile) const { return saveToFile(mainFile) && saveToFile(backupFile); }
bool TestStorage::loadFromAnyFile(const char* mainFile, const char* backupFile) { return loadFromFile(mainFile) || loadFromFile(backupFile); }

const Test* TestStorage::getAt(int index) const {
    if (!arr_ || index < 0 || index >= count_) return nullptr;
    return &arr_[index];
}

void TestStorage::loadDefaultsIfEmpty() {
    if (count_ > 0) return;

    int count = 0;
    const Test* defaults = getDefaultTests(count);

    for (int i = 0; i < count; ++i) {
        addTest(defaults[i]);
    }
}
bool TestStorage::addTest(const Test& test) { if (!arr_ || count_ < 0 || count_ >= maxCount_) return false; arr_[count_++] = test; return true; }
int TestStorage::findById(int id) const { if (!arr_ || count_ <= 0) return -1; for (int i = 0; i < count_; ++i) if (arr_[i].getId() == id) return i; return -1; }
bool TestStorage::updateTest(const Test& test) { int index = findById(test.getId()); if (index == -1) return false; arr_[index] = test; return true; }
bool TestStorage::removeById(int id) { int index = findById(id); if (index == -1) return false; for (int i = index; i < count_ - 1; ++i) arr_[i] = arr_[i + 1]; --count_; return true; }
void TestStorage::printAll() const { if (!arr_ || count_ <= 0) { std::cout << "No tests data to print.\n"; return; } for (int i = 0; i < count_; ++i) { arr_[i].show(); std::cout << "-------------------------\n"; } }
int TestStorage::getCount() const { return count_; }
