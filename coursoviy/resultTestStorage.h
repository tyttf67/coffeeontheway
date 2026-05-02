#pragma once

#include "resultTest.h"

class ResultStorage {
public:
    explicit ResultStorage(int maxCount);
    ~ResultStorage();

    bool saveToFile(const char* fileName) const;
    bool loadFromFile(const char* fileName);
    bool saveToTwoFiles(const char* mainFile, const char* backupFile) const;
    bool loadFromAnyFile(const char* mainFile, const char* backupFile);

    bool addResult(const Result& result);
    int findByQuestionId(int questionId) const;
    bool removeByQuestionId(int questionId);
    void printAll() const;

    int getCount() const;

private:
    Result* arr_;
    int maxCount_;
    int count_;
};
