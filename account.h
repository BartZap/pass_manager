#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <vector>
#include <fstream>
#include <iostream>
//nie wiem do konca czy to dobry pomysl
class Account{
private:
    char pass[20];//generowane haslo
    char domena[20];//domena
    char login[20];//login
    std::vector<std::vector<char> > vec{};
public:
    Account() = default;
    ~Account() = default;
    void logged_in();
};
#endif