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

const char* Test::getQuestionText() const {
    return textQuestion;
}

const char* Test::getAnswerTextForChoice(char choice) const {
    const char normalized = static_cast<char>(std::toupper(static_cast<unsigned char>(choice)));
    for (int i = 0; i < 3; ++i) {
        if (answers[i].key == normalized) {
            return answers[i].text;
        }
    }
    return "";
}

void Test::show() const {
    std::cout << "[" << id << "] " << textQuestion << '\n';
    for (int i = 0; i < 3; ++i) {
        std::cout << answers[i].key << ") " << answers[i].text << '\n';
    }
}

static Test buildQuestion1() {
    Test::AnswerOption options[3] = {
        {'A', "Міцна та інтенсивна", 0},
        {'B', "Збалансована", 1},
        {'C', "М'яка та легка", 2}
    };
    return Test(1, "Яку міцність кави ти надаєш перевагу?", options);
}

static Test buildQuestion2() {
    Test::AnswerOption options[3] = {
        {'A', "Без молока", 3},
        {'B', "Трохи молока", 4},
        {'C', "Багато молока", 2}
    };
    return Test(2, "Скільки молока ти додаєш до кави?", options);
}

static Test buildQuestion3() {
    Test::AnswerOption options[3] = {
        {'A', "Без солодкого", 5},
        {'B', "Трохи солодкості", 6},
        {'C', "Солодкий кавовий десерт", 7}
    };
    return Test(3, "Чи любиш ти солодкий смак кави?", options);
}

static Test buildQuestion4() {
    Test::AnswerOption options[3] = {
        {'A', "Швидкий шот перед роботою", 0},
        {'B', "Класична чашка вдень", 1},
        {'C', "Розслаблюючий вечірній напій", 6}
    };
    return Test(4, "Коли ти зазвичай п'єш каву?", options);
}

static Test buildQuestion5() {
    Test::AnswerOption options[3] = {
        {'A', "Класична гаряча", 3},
        {'B', "Тепла та кремова", 4},
        {'C', "У стилі десерту", 7}
    };
    return Test(5, "Яка температура напою тобі до душі?", options);
}

static Test buildQuestion6() {
    Test::AnswerOption options[3] = {
        {'A', "Потрібен максимальний заряд енергії", 5},
        {'B', "Хочу стабільну зосередженість", 4},
        {'C', "Шукаю затишний настрій", 2}
    };
    return Test(6, "Який у тебе зараз настрій?", options);
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
}
