#pragma once
#include <string>
using namespace std;

class Result{

private:
	int questionId;
	char choice;

public:
	Result();
	Result(int questionId, char choice);
	~Result();


	int  getQuestionId() const;
	char getChoice()  const;
	void show()  const;

};
