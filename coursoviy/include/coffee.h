#pragma once
#include <string>
using namespace std;


class Coffee {

private:

	int id;
	int strength;
	string name;
	string levelRoast;
	string description;
	string syrup;
	bool sugar;
    bool milk;
	

public:

	Coffee();
	Coffee(int id, string name, string levelRoast, int strength, string description, string syrup, bool sugar, bool milk);
	~Coffee();


	string getName() const;
	string getDescription() const;
	string getSyrup() const;
	int getStrength() const;
	bool hasMilk() const;
	bool hasSugar() const;

	void show();

};





// бінарні файли мають зчитуватися і виводитися фціями