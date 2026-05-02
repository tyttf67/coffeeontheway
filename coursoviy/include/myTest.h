#pragma once

class Test {
public:
    struct AnswerOption {
        char key;
        char text[120];
        int coffeeIndex;
    };

private:
    int id;
    char textQuestion[256];
    AnswerOption answers[3];

public:
    Test();
    Test(int id, const char textQuestion[], const AnswerOption answers[3]);
    ~Test();

    int getId() const;
    int getCoffeeIndexForChoice(char choice) const;

    void show() const;
};

const Test* getDefaultTests(int& count);
