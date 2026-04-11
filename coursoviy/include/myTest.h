#pragma once
#include <string>
using namespace std;

class Test {

    private:
	int id;
	string textQuestion;
	string optionA;
	string optionB;
	string optionC;
	string optionD;
	string optionE;
	string optionF;

public:
	Test();
	Test(
		int id, string textQuestion,
		string A, string B, string C,
		string D, string E, string F
	);
	~Test();

	int getId() const;
	string getQuestion() const;

	void show() const;





};
