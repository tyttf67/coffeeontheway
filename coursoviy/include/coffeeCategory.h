#pragma once
#include <string>
using namespace std;

class CoffeeCategory {

private:
    int id;
    string name;      
    string description;

public:
    CoffeeCategory();
    CoffeeCategory(int id, string name, string description);
    ~CoffeeCategory();

    string getName() const;
    string getDescription() const;

    void show();

};
