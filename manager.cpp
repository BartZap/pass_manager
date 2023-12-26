#include "manager.h"
#include "account.h"

Manager::Manager() = default;
Manager::~Manager() = default;
void Manager::start_screen(){
    bool steer = true;
    int choice{};
    read_users();
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
                log_in();
                break;
            }
            case 2:
            {
                //PROBLEM PRZY PODAWANIU TEGO SAMEGO LOGINU
                //USUWA ZAWARTOSC PLIKU TXT
                over_write();
                break;
            }
            case 3:
            {
                system("cls");
                std::cout << "Bye" << std::endl;
                steer = false;
                break;
            }
            default:
            {
                system("cls");
                std::cout << "Wrong action !" << std::endl;
                break;
            }
        }
    }
}
void Manager::create_account(){
    system("cls");
    std::cout << "Enter your login : ";
    std::cin >> login;
    std::cout << "Enter your password : ";
    std::cin >> password;
    auto check = logs.find(login);
    if(check == logs.end()){
        logs[login] = password;
        std::cout << "Your account with login : " << login << " has been created" << std::endl;
        std::cout << "Log in for more informations" << std::endl;
    }else{
        std::cout << "Passed login already exists in database, please change it." << std::endl;
    }
}
void Manager::read_users(){
    //wpisanie do mapy zeby dola rade szukac istniejace loginy
    plik.open("napisy.txt",std::ios::out);
    int nr_linii = 1;
    while(std::getline(plik,napis)){
        //zczytywanie pliku
        switch(nr_linii){
            case 1:
                login = napis;
                break;
            case 0:
                password = napis;
                logs[login] = password;
                break;
            default:
                std::cout << "Bad file" << std::endl;
                break;
        }
        nr_linii++;
        nr_linii = nr_linii % 2;
    }
    plik.close();
}
void Manager::over_write(){
    //nadpisywanie uzytkownikow 
    system("cls");
    read_users();
    plik2.open("napisy.txt",std::ios::trunc);
    std::cout << "Podaj login : " ;
    std::cin >> login ;
    std::cout << "Podaj haslo : ";
    std::cin >> password;
    auto can_can = logs.find(login);
    try{
        if(can_can == logs.end())//czy nie istnieje juz taki login
            logs[login] = password;
        else
            throw "Podany login istnieje" ;
    }catch(const char* exception){
        std::cout << exception << std::endl;
    }
    can_can = logs.begin();
    while(can_can != logs.end()){
        //wpisywanie do pliku
        plik2 << can_can -> first;
        plik2 << "\n";
        plik2 << can_can -> second;
        plik2 << "\n";
        can_can++;
    }
    plik2.close();
}
void Manager::log_in(){
    system("cls");
    std::cout << "Podaj swoj login : ";
    std::cin >> login;
    std::cout << "Podaj haslo : ";
    std::cin >> password;
    auto check = logs.find(login);
    if(check != logs.end()){
        if(check -> second == password)
            std::cout << "Udane logowanie !" << std::endl;
    }else{
        std::cout << "Nie poprawny login lub haslo." << std::endl;
        start_screen();
    }
}
