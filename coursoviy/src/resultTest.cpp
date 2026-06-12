#include <iostream>
#include "resultTest.h"

Result::Result() : userId(0), attemptId(0), questionId(0), choice(0), coffeeId(0) {}

Result::Result(int questionId, char choice)
    : userId(0), attemptId(0), questionId(questionId), choice(choice), coffeeId(0) {
}

Result::Result(int userId, int attemptId, int questionId, char choice)
    : userId(userId), attemptId(attemptId), questionId(questionId), choice(choice), coffeeId(0) {
}

Result::~Result() {}

int Result::getUserId() const { return userId; }
int Result::getAttemptId() const { return attemptId; }
int Result::getQuestionId() const { return questionId; }
char Result::getChoice() const { return choice; }
int Result::getCoffeeId() const { return coffeeId; }
void Result::setCoffeeId(int id) { coffeeId = id; }

void Result::show() const {
    std::cout << "User ID: " << userId << std::endl;
    std::cout << "Attempt ID: " << attemptId << std::endl;
    std::cout << "Question ID: " << questionId << std::endl;
    std::cout << "Choice: " << choice << std::endl;
    std::cout << "Coffee ID: " << coffeeId << std::endl;
}