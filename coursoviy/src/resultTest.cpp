#include <iostream>
#include "resultTest.h"

Result::Result() {

	questionId = 0;
	choice = 0;

	cout << "it's constructor without parametrs" << endl;
};

Result::Result(int questionId, char choice) {

	this->questionId = questionId;
	this->choice = choice;

	cout << "it's constructor with parametrs" << endl;
};

Result::~Result() {

	cout << "it's destructor" << endl;

};

int Result::getQuestionId() const {

	return questionId;
};

char Result::getChoice()const {

	return choice;
};

void Result::show() const {

	cout << "Question ID: " << questionId << endl;
	cout << "Choice: " << choice << endl;
};
