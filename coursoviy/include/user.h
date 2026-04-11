#pragma once
#include <string>
using namespace std;

class User {

private:
	int id;
	string name;
	string answears;
	string favouriteDrinks;

public:

	User();
	User(int id, string name, string answears, string favouriteDrinks);
	~User();


	string getName() const;
	string getAnswears() const;
	string getFavouriteDrinks() const;

	void show();

	//доробити гетери , сетери
};