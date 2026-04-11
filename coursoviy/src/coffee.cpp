#include <iostream>
#include "coffee.h"

Coffee::Coffee(){

	id = 0;
	strength = 1;
	name = "";
	levelRoast = "";
    description = "";
    syrup = "";  // можливо зробити масив для сиропів (вибір)
    sugar = false;
	milk = false;
    
    cout << "it's constructor without parametrs";
};

Coffee::Coffee(  

    int id, string name,
    string levelRoast, int strength,
    string description, string syrup, 
    bool sugar, bool milk

){

    this->id = id;
    this->name = name;
    this->levelRoast = levelRoast;
    this->strength = strength;
    this->description = description;
    this->syrup = syrup;
    this->sugar = sugar;
    this->milk = milk;

    cout << "it's constructor with parametrs";

};

Coffee::~Coffee() {
    cout << "it is destructor";
};

string Coffee::getName() const {

    return name;
};

string Coffee::getDescription() const {

    return description;
};

string Coffee::getSyrup()const {

    return syrup;
}

int Coffee::getStrength() const
{
    return strength;
};

bool Coffee::hasMilk() const {

    return milk;

};
bool Coffee::hasSugar() const {

    return sugar;

};

void Coffee::show() {
    cout << "Name: " << name << endl;
    cout << "Strength: " << strength << endl;

    if (milk == true) {
        cout << "Milk: Yes" << endl;
    }
    else {
        cout << "Milk: No" << endl;
    }

    if (sugar == true) {
        cout << "Sugar: Yes" << endl;
    }
    else {
        cout << "Sugar: No" << endl;
    }

    cout << "Syrup: " << syrup << endl;
    cout << "Description: " << description << endl;

};
