#pragma once
#include <string>

using namespace std;

class Result {

private:
    int userId;
    int attemptId;
    int questionId;
    char choice;

public:
    Result();
    Result(int questionId, char choice);
    Result(int userId, int attemptId, int questionId, char choice);
    ~Result();

    int getUserId() const;
    int getAttemptId() const;
    int getQuestionId() const;
    char getChoice() const;
    void show() const;
   
};
