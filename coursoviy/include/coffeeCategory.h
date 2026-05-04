#pragma once

class CoffeeCategory {

private:
    int id;
    char name[100];
    char description[100];

public:
    CoffeeCategory();
    CoffeeCategory(int id, const char* name, const char* description);
    ~CoffeeCategory();


    int getId() const;
    const char* getName() const;
    const char* getDescription() const;

    void show() const;
    
};
