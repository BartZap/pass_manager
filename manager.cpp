#include "manager.h"
#include "account.h"

Manager::Manager() = default;
Manager::~Manager() = default;
void Manager::start_screen(){
    bool steer = true;
    int choice{};
    while(true){
    std::cout << "----Welcome to password manager----" << std::endl;
    std::cout << "Choose action : " << std::endl;
    std::cout << "1. Log in." << std::endl;
    std::cout << "2. Create an account." << std::endl;
    std::cout << "3. Quit." << std::endl;
    std::cout << "Action : ";
    std::cin >> choice;
    switch(choice){
        case 1:
        {
            check_login();
            break;
        }
        case 2:
        {
            create_account();
            break;
        }
        case 3:
        {
            system("clear");
            std::cout << "Bye" << std::endl;
            steer = false;
            break;
        }
        default:
        {
            system("clear");
            std::cout << "Wrong action !" << std::endl;
            break;
        }
    }
    }
}
void Manager::check_login(){
    system("clear");
    std::cout << "Enter your login : ";
    std::cin >> login;
    std::cout << "Enter your password : ";
    std::cin >> password;
    auto check = users.find(login);
    if((check != users.end()) && (check -> second == password)){
        std::cout << "You have been logged in succesfully" << std::endl;
        Account ac1;
        ac1.logged_in();
    }else{
        std::cout << "Passed wrong password or login, check next time." << std::endl;
    }
}
void Manager::create_account(){
    system("clear");
    std::cout << "Enter your login : ";
    std::cin >> login;
    std::cout << "Enter your password : ";
    std::cin >> password;
    auto check = users.find(login);
    if(check == users.end()){
        users[login] = password;
        std::cout << "Your account with login : " << login << " has been created" << std::endl;
        std::cout << "Log in for more informations" << std::endl;
    }else{
        std::cout << "Passed login already exists in database, please change it." << std::endl;
    }
}