#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include "myTest.h"

static void copyText(char* dest, size_t size, const char* src) {
    if (dest == nullptr || size == 0) return;
#ifdef _MSC_VER
    strncpy_s(dest, size, src ? src : "", _TRUNCATE);
#else
    std::strncpy(dest, src ? src : "", size - 1);
#endif
    dest[size - 1] = '\0';
}

Test::Test() : id(0) {
    copyText(textQuestion, sizeof(textQuestion), "");
    for (int i = 0; i < 3; ++i) {
        answers[i].key = 'A';
        copyText(answers[i].text, sizeof(answers[i].text), "");
        answers[i].coffeeIndex = 0;
    }
}

Test::Test(int id, const char textQuestion[], const AnswerOption answers[])
    : id(id) {
    copyText(this->textQuestion, sizeof(this->textQuestion), textQuestion);
    for (int i = 0; i < 3; ++i) {
        this->answers[i].key = answers[i].key;
        copyText(this->answers[i].text, sizeof(this->answers[i].text), answers[i].text);
        this->answers[i].coffeeIndex = answers[i].coffeeIndex;
    }
}

Test::~Test() {}

int Test::getId() const {
    return id;
}

int Test::getCoffeeIndexForChoice(char choice) const {
    const char normalized = static_cast<char>(std::toupper(static_cast<unsigned char>(choice)));
    for (int i = 0; i < 3; ++i) {
        if (answers[i].key == normalized) {
            return answers[i].coffeeIndex;
        }
    }
    return -1;
}

void Test::show() const {
    std::cout << "[" << id << "] " << textQuestion << '\n';
    for (int i = 0; i < 3; ++i) {
        std::cout << answers[i].key << ") " << answers[i].text << '\n';
    }
}

static Test buildQuestion1() {
    Test::AnswerOption options[3] = {
        {'A', "Strong and intense", 0},
        {'B', "Balanced", 1},
        {'C', "Soft and light", 2}
    };
    return Test(1, "Which coffee strength do you prefer?", options);
}

static Test buildQuestion2() {
    Test::AnswerOption options[3] = {
        {'A', "No milk", 3},
        {'B', "A little milk", 4},
        {'C', "More milk", 2}
    };
    return Test(2, "How much milk do you like?", options);
}

static Test buildQuestion3() {
    Test::AnswerOption options[3] = {
        {'A', "No sweet notes", 5},
        {'B', "A little sweetness", 6},
        {'C', "Sweet coffee dessert", 7}
    };
    return Test(3, "Do you enjoy sweet coffee taste?", options);
}

static Test buildQuestion4() {
    Test::AnswerOption options[3] = {
        {'A', "Quick shot before work", 0},
        {'B', "Classic daytime cup", 1},
        {'C', "Relaxing evening drink", 6}
    };
    return Test(4, "When do you usually drink coffee?", options);
}

static Test buildQuestion5() {
    Test::AnswerOption options[3] = {
        {'A', "Classic hot", 3},
        {'B', "Warm and creamy", 4},
        {'C', "Dessert style", 7}
    };
    return Test(5, "What temperature/style feels right now?", options);
}

static Test buildQuestion6() {
    Test::AnswerOption options[3] = {
        {'A', "Need maximum energy", 5},
        {'B', "Need stable focus", 4},
        {'C', "Want cozy mood", 2}
    };
    return Test(6, "What is your current mood?", options);
}

const Test* getDefaultTests(int& count) {
    static Test tests[6] = {
        buildQuestion1(),
        buildQuestion2(),
        buildQuestion3(),
        buildQuestion4(),
        buildQuestion5(),
        buildQuestion6()
    };
    count = 6;
    return tests;
}\n
