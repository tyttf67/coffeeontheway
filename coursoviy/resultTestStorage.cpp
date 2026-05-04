#include "storage.h"
#include <fstream>
#include <iostream>

ResultStorage::ResultStorage(int maxCount) : arr_(nullptr), maxCount_(maxCount), count_(0) {
    if (maxCount_ > 0) arr_ = new Result[maxCount_];
    else maxCount_ = 0;
}

ResultStorage::~ResultStorage() { delete[] arr_; }

bool ResultStorage::saveToFile(const char* fileName) const {
    if (!fileName || !arr_) return false;
    std::ofstream out(fileName, std::ios::binary);
    if (!out.is_open()) return false;
    out.write(reinterpret_cast<const char*>(&count_), sizeof(count_));
    if (!out.good()) return false;
    for (int i = 0; i < count_; ++i) {
        out.write(reinterpret_cast<const char*>(&arr_[i]), sizeof(Result));
        if (!out.good()) return false;
    }
    return true;
}

bool ResultStorage::loadFromFile(const char* fileName) {
    count_ = 0;
    if (!fileName || !arr_ || maxCount_ <= 0) return false;
    std::ifstream in(fileName, std::ios::binary);
    if (!in.is_open()) return false;
    int countInFile = 0;
    in.read(reinterpret_cast<char*>(&countInFile), sizeof(countInFile));
    if (!in.good() || countInFile < 0 || countInFile > maxCount_) return false;
    for (int i = 0; i < countInFile; ++i) {
        in.read(reinterpret_cast<char*>(&arr_[i]), sizeof(Result));
        if (!in.good()) return false;
    }
    count_ = countInFile;
    return true;
}

bool ResultStorage::saveToTwoFiles(const char* mainFile, const char* backupFile) const { return saveToFile(mainFile) && saveToFile(backupFile); }
bool ResultStorage::loadFromAnyFile(const char* mainFile, const char* backupFile) { return loadFromFile(mainFile) || loadFromFile(backupFile); }

bool ResultStorage::addResult(const Result& result) {
    if (!arr_ || count_ < 0 || count_ >= maxCount_) return false;
    arr_[count_++] = result;
    return true;
}

int ResultStorage::getNextAttemptIdForUser(int userId) const {
    int maxAttemptForUser = 0;
    for (int i = 0; i < count_; ++i) {
        if (arr_[i].getUserId() == userId && arr_[i].getAttemptId() > maxAttemptForUser) {
            maxAttemptForUser = arr_[i].getAttemptId();
        }
    }
    return maxAttemptForUser + 1;
}

bool ResultStorage::addAnswerForUserAttempt(int userId, int attemptId, int questionId, char choice) {
    return addResult(Result(userId, attemptId, questionId, choice));
}

void ResultStorage::printHistoryForUser(int userId) const {
    bool found = false;
    for (int i = 0; i < count_; ++i) {
        if (arr_[i].getUserId() == userId) {
            if (!found) {
                std::cout << "\n=== Test history ===\n";
            }
            arr_[i].show();
            std::cout << "-------------------------\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No test history for current user yet.\n";
    }
}

int ResultStorage::findByQuestionId(int questionId) const { if (!arr_ || count_ <= 0) return -1; for (int i = 0; i < count_; ++i) if (arr_[i].getQuestionId() == questionId) return i; return -1; }
bool ResultStorage::updateByIndex(int index, const Result& result) { if (!arr_ || index < 0 || index >= count_) return false; arr_[index] = result; return true; }
bool ResultStorage::removeByQuestionId(int questionId) { int index = findByQuestionId(questionId); if (index == -1) return false; for (int i = index; i < count_ - 1; ++i) arr_[i] = arr_[i + 1]; --count_; return true; }
int ResultStorage::removeByUserId(int userId) {
    if (!arr_ || count_ <= 0) return 0;

    int removed = 0;
    for (int i = 0; i < count_;) {
        if (arr_[i].getUserId() == userId) {
            for (int j = i; j < count_ - 1; ++j) {
                arr_[j] = arr_[j + 1];
            }
            --count_;
            ++removed;
        } else {
            ++i;
        }
    }

    return removed;
}
void ResultStorage::printAll() const { if (!arr_ || count_ <= 0) { std::cout << "No results data to print.\n"; return; } for (int i = 0; i < count_; ++i) arr_[i].show(); }
const Result* ResultStorage::data() const { return arr_; }
int ResultStorage::getCount() const { return count_; }
