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

    const char* getLogin() const;
    const char* getPassword() const;
    void setProfile(int id, const char* name, const char* login, const char* gmail, const char* password, const char* favouriteDrinks);
    bool hasCredentials() const;

    bool verify(const char* inputLogin, const char* inputPassword);
    bool isVerified() const;

    void show() const;
};
