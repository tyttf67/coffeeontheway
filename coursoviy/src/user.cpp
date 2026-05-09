#include "user.h"
#include <cstring>
#include <iostream>

static void copyText(char* dest, size_t size, const char* src) {
    if (dest == nullptr || size == 0) return;
#ifdef _MSC_VER
    strncpy_s(dest, size, src ? src : "", _TRUNCATE);
#else
    std::strncpy(dest, src ? src : "", size - 1);
#endif
    dest[size - 1] = '\0';
}

User::User() : id(0), verified(false) {
    copyText(name, sizeof(name), "");
    copyText(login, sizeof(login), "");
    copyText(gmail, sizeof(gmail), "");
    copyText(password, sizeof(password), "");
    copyText(favouriteDrinks, sizeof(favouriteDrinks), "");
}

User::User(int id, const char* name, const char* login,const char* gmail, const char* password, const char* favouriteDrinks)
    : id(id), verified(false) {
    copyText(this->name, sizeof(this->name), name);
    copyText(this->login, sizeof(this->login), login);
    copyText(this->gmail, sizeof(this->gmail), gmail);
    copyText(this->password, sizeof(this->password), password);
    copyText(this->favouriteDrinks, sizeof(this->favouriteDrinks), favouriteDrinks);
}

User::~User() {}

int User::getId() const { return id; }
const char* User::getName() const { return name; }
const char* User::getLogin() const { return login; }
const char* User::getGmail() const { return gmail; }
const char* User::getPassword() const { return password; }
const char* User::getFavouriteDrinks() const { return favouriteDrinks; }

void User::setProfile(int id, const char* name, const char* login, const char* gmail ,const char* password, const char* favouriteDrinks) {
    this->id = id;
    copyText(this->name, sizeof(this->name), name);
    copyText(this->login, sizeof(this->login), login);
    copyText(this->gmail, sizeof(this->gmail), gmail);
    copyText(this->password, sizeof(this->password), password);
    copyText(this->favouriteDrinks, sizeof(this->favouriteDrinks), favouriteDrinks);
    verified = false;
}

bool User::addFavouriteDrink(const char* drinkName) {
    if (!drinkName || drinkName[0] == '\0') return false;
    if (std::strstr(favouriteDrinks, drinkName) != nullptr) return true;

    const size_t currentLength = std::strlen(favouriteDrinks);
    const size_t drinkLength = std::strlen(drinkName);
    const size_t separatorLength = currentLength > 0 ? 2 : 0;

    if (currentLength + separatorLength + drinkLength >= sizeof(favouriteDrinks)) {
        return false;
    }

    if (currentLength > 0) {
#ifdef _MSC_VER
        strcat_s(favouriteDrinks, sizeof(favouriteDrinks), ", ");
#else
        std::strcat(favouriteDrinks, ", ");
#endif
    }
#ifdef _MSC_VER
    strcat_s(favouriteDrinks, sizeof(favouriteDrinks), drinkName);
#else
    std::strcat(favouriteDrinks, drinkName);
#endif
    return true;
}

bool User::hasCredentials() const {
    return login[0] != '\0' && password[0] != '\0';
}

bool User::verify(const char* inputLogin, const char* inputPassword) {
    verified =
        std::strcmp(login, inputLogin ? inputLogin : "") == 0 &&
        std::strcmp(password, inputPassword ? inputPassword : "") == 0;
    return verified;
}

bool User::isVerified() const { return verified; }

void User::show() const {
    std::cout << "ID: " << id << "\nName: " << name
        << "\nLogin: " << login
        << "\nGmail: " << gmail
        << "\nFavourite drinks: " << favouriteDrinks << '\n';
}

