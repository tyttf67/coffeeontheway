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

    std::cout << "it's constructor without parametrs";
}

CoffeeCategory::CoffeeCategory(int id, const char* name, const char* description) {
    this->id = id;
    copyText(this->name, sizeof(this->name), name);
    copyText(this->description, sizeof(this->description), description);

    std::cout << "it's constructor with parametrs";
}

CoffeeCategory::~CoffeeCategory() {
    std::cout << "it's destructor" << std::endl;
}

int CoffeeCategory::getId() const{
    return id;
}

void CoffeeCategory::show() const{
    std::cout << "Id: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Description: " << description << std::endl;
}
bool CoffeeCategory::writeToFile(std::ofstream& out) const {
    if (!out.is_open()) return false;

    out.write(reinterpret_cast<const char*>(&id), sizeof(id));
    out.write(name, sizeof(name));
    out.write(description, sizeof(description));

    return out.good();
}

bool CoffeeCategory::readFromFile(std::ifstream& in) {
    if (!in.is_open()) return false;

    in.read(reinterpret_cast<char*>(&id), sizeof(id));
    in.read(name, sizeof(name));
    in.read(description, sizeof(description));

    name[sizeof(name) - 1] = '\0';
    description[sizeof(description) - 1] = '\0';

    return in.good();
}
