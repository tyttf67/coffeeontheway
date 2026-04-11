#include <iostream>
#include "coffeeCategory.h"

CoffeeCategory::CoffeeCategory() {

	id = 0;
    name = "";
	description = "";

	cout << "it's constructor without parametrs";

}

CoffeeCategory::CoffeeCategory(int id, string name, string description) {

	this->id = id;
	this->name = name;
	this->description = description;

	cout << "it's constructor with parametrs";
};

CoffeeCategory::~CoffeeCategory() {

	cout << "it's destructor"<< endl;
};

string CoffeeCategory::getName() const {

	return name;
};

string CoffeeCategory::getDescription() const {

	return description;
};

void CoffeeCategory::show() {
	cout << "Name: " << name << endl;
	cout << "Description: " << description << endl;

};
