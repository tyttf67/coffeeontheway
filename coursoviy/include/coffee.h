#pragma once
class Coffee {

private:
    int id;
    char coffees[512];
    int strength;
    char name[100];
    char levelRoast[100];
    char description[100];
    char syrup[100];
    bool sugar;
    bool milk;

public:
    Coffee();
    Coffee(int id,const char* coffees, const char* name, const char* levelRoast, int strength, const char* description, const char* syrup, bool sugar, bool milk);
    ~Coffee();

    int getId() const;
    const char* getCoffeeArray() const; // юзаю сутніть кофі груп
    const char* getName() const;         // поле цього класу дає назву
  

    void show() const;
};
