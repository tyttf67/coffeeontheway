#include <iostream>
#include <fstream>
#include "resultTest.h"

Result::Result() {
    userId = 0;
    attemptId = 0;
    questionId = 0;
    choice = 0;
}

Result::Result(int questionId, char choice) {
    userId = 0;
    attemptId = 0;
    this->questionId = questionId;
    this->choice = choice;
}

Result::Result(int userId, int attemptId, int questionId, char choice) {
    this->userId = userId;
    this->attemptId = attemptId;
    this->questionId = questionId;
    this->choice = choice;
}

Result::~Result() {}

int Result::getUserId() const {
    return userId;
}

int Result::getAttemptId() const {
    return attemptId;
}

int Result::getQuestionId() const {
    return questionId;
}

char Result::getChoice() const {
    return choice;
}

void Result::show() const {
    cout << "User ID: " << userId << endl;
    cout << "Attempt ID: " << attemptId << endl;
    cout << "Question ID: " << questionId << endl;
    cout << "Choice: " << choice << endl;
}

bool Result::writeToFile(std::ofstream& out) const {
    out.write(reinterpret_cast<const char*>(&userId), sizeof(userId));
    out.write(reinterpret_cast<const char*>(&attemptId), sizeof(attemptId));
    out.write(reinterpret_cast<const char*>(&questionId), sizeof(questionId));
    out.write(reinterpret_cast<const char*>(&choice), sizeof(choice));
    return out.good();
}

bool Result::readFromFile(std::ifstream& in) {
    in.read(reinterpret_cast<char*>(&userId), sizeof(userId));
    in.read(reinterpret_cast<char*>(&attemptId), sizeof(attemptId));
    in.read(reinterpret_cast<char*>(&questionId), sizeof(questionId));
    in.read(reinterpret_cast<char*>(&choice), sizeof(choice));
    return in.good();
}
