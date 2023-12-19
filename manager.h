#ifndef MANAGER_H
#define MANAGER_H
#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <map>

class Manager{
private:
    std::map<std::string, std::string> users{};
    std::string login{},password{};
    size_t y{};
public:
    Manager();
    ~Manager();
    void start_screen();
    void create_account();
    void check_login();
};
#endif