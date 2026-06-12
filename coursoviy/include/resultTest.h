#pragma once

class Result {
private:
    int userId;
    int attemptId;
    int questionId;
    char choice;
    int coffeeId;

public:
    Result();
    Result(int questionId, char choice);
    Result(int userId, int attemptId, int questionId, char choice);
    ~Result();

    int getUserId() const;
    int getAttemptId() const;
    int getQuestionId() const;
    char getChoice() const;
    int getCoffeeId() const;
    void setCoffeeId(int id);
    void show() const;
};