#include "resultTestStorage.h"
#include <fstream>
#include <iostream>

ResultStorage::ResultStorage(int maxCount) : arr_(nullptr), maxCount_(maxCount), count_(0) {
    if (maxCount_ > 0) arr_ = new Result[maxCount_];
    else maxCount_ = 0;
}

ResultStorage::~ResultStorage() { delete[] arr_; }

bool ResultStorage::saveToFile(const char* fileName) const {
    if (fileName == nullptr || arr_ == nullptr || count_ < 0) return false;
    std::ofstream out(fileName, std::ios::binary);
    if (!out.is_open()) return false;
    out.write(reinterpret_cast<const char*>(&count_), sizeof(count_));
    if (!out.good()) return false;
    for (int i = 0; i < count_; ++i) if (!arr_[i].writeToFile(out)) return false;
    return true;
}

bool ResultStorage::loadFromFile(const char* fileName) {
    count_ = 0;
    if (fileName == nullptr || arr_ == nullptr || maxCount_ <= 0) return false;
    std::ifstream in(fileName, std::ios::binary);
    if (!in.is_open()) return false;
    int countInFile = 0;
    in.read(reinterpret_cast<char*>(&countInFile), sizeof(countInFile));
    if (!in.good() || countInFile < 0 || countInFile > maxCount_) return false;
    for (int i = 0; i < countInFile; ++i) if (!arr_[i].readFromFile(in)) return false;
    count_ = countInFile;
    return true;
}

bool ResultStorage::saveToTwoFiles(const char* mainFile, const char* backupFile) const { return saveToFile(mainFile) && saveToFile(backupFile); }

bool ResultStorage::loadFromAnyFile(const char* mainFile, const char* backupFile) {
    if (loadFromFile(mainFile)) return true;
    return loadFromFile(backupFile);
}

bool ResultStorage::addResult(const Result& result) {
    if (arr_ == nullptr || maxCount_ <= 0 || count_ < 0 || count_ >= maxCount_) return false;
    arr_[count_++] = result;
    return true;
}

int ResultStorage::findByQuestionId(int questionId) const {
    if (arr_ == nullptr || count_ <= 0) return -1;
    for (int i = 0; i < count_; ++i) if (arr_[i].getQuestionId() == questionId) return i;
    return -1;
}

bool ResultStorage::removeByQuestionId(int questionId) {
    if (arr_ == nullptr || count_ <= 0) return false;
    const int index = findByQuestionId(questionId);
    if (index == -1) return false;
    for (int i = index; i < count_ - 1; ++i) arr_[i] = arr_[i + 1];
    --count_;
    return true;
}

void ResultStorage::printAll() const {
    if (arr_ == nullptr || count_ <= 0) { std::cout << "No results data to print.\n"; return; }
    for (int i = 0; i < count_; ++i) arr_[i].show();
}

int ResultStorage::getCount() const { return count_; }
