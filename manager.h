#ifndef MANAGER_H
#define MANAGER_H
#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>
#include <vector>
#include <random>
//#include <conio.h>

class Manager{
private:
    static const int MAX_PASS_LEN = 20;
    std::string napis{},domain{},password{},login{};
    size_t y{};
    std::ifstream plik;
    std::ofstream plik2;
    std::map<std::string,std::string> logs{};
    char pass[MAX_PASS_LEN];
public:
    Manager();
    ~Manager();
    std::string get_login();
    std::string cipher(std::string& , size_t, bool);
    void start_screen();
    void create_account();
    void check_login();
    void read_users(std::string sciezka = "napisy.txt");
    void over_write(std::string sciezka = "napisy.txt");
    void log_in();
    void private_account();
    void generate_pass();
    void show_my_info();
    void delete_pass();
};
#endif