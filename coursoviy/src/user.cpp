#include "user.h"
#include <iostream>

User::User() {

	id = 0;
	name = "";
	answears = "";
	favouriteDrinks = "";

	cout << "constructor without parametrs";
};

User::User(int id, string name, string answears, string favouriteDrinks) {

	this->id = id;
	this->name = name;
	this->answears = answears;
	this->favouriteDrinks = favouriteDrinks;

	cout << "constructor with parametrs";

};
 
User::~User() {

	cout << "it's destructor" << endl;
};

string User::getName() const {

	return name;
};

string  User::getAnswears() const {

	return answears;
	  
};

string User::getFavouriteDrinks() const {

	return favouriteDrinks;
};

void User::show() {

	cout << "Name: " << name << endl;
	cout << "Answers: " << answears << endl;
	cout << "Favourite drinks: " << favouriteDrinks << endl;
};
