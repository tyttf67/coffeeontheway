
#include <iostream>
#include <string>
#include "myTest.h"

Test::Test() {
    id = 0;
    textQuestion = "";
    optionA = "";
    optionB = "";
    optionC = "";
    optionD = "";
    optionE = "";
    optionF = "";

    cout << "it's constructor without parametrs";
};

Test::Test(int id, string textQuestion,
    string A, string B, string C,
    string D, string E, string F) {

    this->id = id;
    this->textQuestion = textQuestion;
    optionA = A;
    optionB = B;
    optionC = C;
    optionD = D;
    optionE = E;
    optionF = F;

    cout << "it's constructor with parametrs" << endl;
};

Test::~Test() {

    cout << "it's destructor" << endl;
};

int Test::getId() const {
    return id;
}

string Test::getQuestion() const {
    return textQuestion;
}

void Test::show() const {
    cout << "ID: " << id << endl;
    cout << "Question: " << textQuestion << endl;

    cout << "A) " << optionA << endl;
    cout << "B) " << optionB << endl;
    cout << "C) " << optionC << endl;
    cout << "D) " << optionD << endl;
    cout << "E) " << optionE << endl;
    cout << "F) " << optionF << endl;
};