#pragma once
class User {
private:
    int id;
    char name[100];
    char login[64];
    char gmail[100];
    char password[64];
    char favouriteDrinks[100];
    bool verified;

public:
    User();
    User(int id, const char* name, const char* login, const char* gmail, const char* password, const char* favouriteDrinks);
    ~User();

    int getId() const;
    const char* getName() const;
    const char* getLogin() const;
    const char* getGmail() const;
    const char* getPassword() const;
    const char* getFavouriteDrinks() const;
    void setProfile(int id, const char* name, const char* login, const char* gmail, const char* password, const char* favouriteDrinks);
    bool addFavouriteDrink(const char* drinkName);
    bool hasCredentials() const;

    bool verify(const char* inputLogin, const char* inputPassword);
    bool isVerified() const;

    void show() const;
};
