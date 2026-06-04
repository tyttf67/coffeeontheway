#include <iostream>
#include <cstring>
#include "coffee.h"

static void copyText(char* dest, size_t size, const char* src) {
    if (dest == nullptr || size == 0) return;
#ifdef _MSC_VER
    strncpy_s(dest, size, src ? src : "", _TRUNCATE);
#else
    std::strncpy(dest, src ? src : "", size - 1);
#endif
    dest[size - 1] = '\0';
}

Coffee::Coffee() : id(0), categoryId(0), strength(1), sugar(false), milk(false) {
    copyText(name, sizeof(name), "");
    copyText(levelRoast, sizeof(levelRoast), "");
    copyText(description, sizeof(description), "");
    copyText(syrup, sizeof(syrup), "");
}

Coffee::Coffee(
    int id,
    int categoryId,
    const char* name,
    const char* levelRoast,
    int strength,
    const char* description,
    const char* syrup,
    bool sugar,
    bool milk
) : id(id), categoryId(categoryId), strength(strength), sugar(sugar), milk(milk) {
    copyText(this->name, sizeof(this->name), name);
    copyText(this->levelRoast, sizeof(this->levelRoast), levelRoast);
    copyText(this->description, sizeof(this->description), description);
    copyText(this->syrup, sizeof(this->syrup), syrup);
}

Coffee::~Coffee() {};

int Coffee::getId() const {
    return id;
};

int Coffee::getCategoryId() const {
    return categoryId;
};

const char* Coffee::getName() const {
    return name;
};
int Coffee::getStrength() const { return strength; }
const char* Coffee::getLevelRoast() const { return levelRoast; }
const char* Coffee::getDescription() const { return description; }
const char* Coffee::getSyrup() const { return syrup; }
bool Coffee::getSugar() const { return sugar; }
bool Coffee::getMilk() const { return milk; }


void Coffee::show() const {
    std::cout << "ID: " << id << '\n';
    std::cout << "Name: " << name << '\n';
    std::cout << "Category ID: " << categoryId << '\n';
    std::cout << "Roast level: " << levelRoast << '\n';
    std::cout << "Strength (1-5): " << strength << '\n';
    std::cout << "Milk: " << (milk ? "Yes" : "No") << '\n';
    std::cout << "Sugar: " << (sugar ? "Yes" : "No") << '\n';
    std::cout << "Syrup: " << syrup << '\n';
    std::cout << "Description: " << description << '\n';
}
