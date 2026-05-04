#include <iostream>
#include <cstring>
#include "coffeeCategory.h"

static void copyText(char* dest, size_t size, const char* src) {
    if (dest == nullptr || size == 0) return;
#ifdef _MSC_VER
    strncpy_s(dest, size, src ? src : "", _TRUNCATE);
#else
    std::strncpy(dest, src ? src : "", size - 1);
#endif
    dest[size - 1] = '\0';
}

CoffeeCategory::CoffeeCategory() {
    id = 0;
    copyText(name, sizeof(name), "");
    copyText(description, sizeof(description), "");

    //std::cout << "it's constructor without parametrs";
}

CoffeeCategory::CoffeeCategory(int id, const char* name, const char* description) {
    this->id = id;
    copyText(this->name, sizeof(this->name), name);
    copyText(this->description, sizeof(this->description), description);

    //std::cout << "it's constructor with parametrs";
}

CoffeeCategory::~CoffeeCategory() {
    //std::cout << "it's destructor" << std::endl;
}

int CoffeeCategory::getId() const{
    return id;
}

const char* CoffeeCategory::getName() const {
    return name;
}

const char* CoffeeCategory::getDescription() const {
    return description;
}

void CoffeeCategory::show() const{
    std::cout << "Id: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Description: " << description << std::endl;
}

