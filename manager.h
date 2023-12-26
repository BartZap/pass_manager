#ifndef MANAGER_H
#define MANAGER_H
#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>

class Manager{
private:
    std::string napis{},login{},password{};
    size_t y{};
    std::ifstream plik;
    std::ofstream plik2;
    std::map<std::string,std::string> logs{};
public:
    Manager();
    ~Manager();
    void start_screen();
    void create_account();
    void check_login();
    void read_users();
    void over_write();
    void log_in();
};
#endif
