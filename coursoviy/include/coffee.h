#pragma once
class Coffee {
private:
    int id;
    int categoryId;
    int strength;
    char name[100];
    char levelRoast[100];
    char description[1024];
    char syrup[100];
    bool sugar;
    bool milk;

public:
    Coffee();
    Coffee(int id, int categoryId, const char* name, const char* levelRoast, int strength, const char* description, const char* syrup, bool sugar, bool milk);
    ~Coffee();

    int getId() const;
    int getCategoryId() const;
    int getStrength() const;
    const char* getName() const;
    const char* getLevelRoast() const;
    const char* getDescription() const;
    const char* getSyrup() const;
    bool getSugar() const;
    bool getMilk() const;

    void show() const;
};