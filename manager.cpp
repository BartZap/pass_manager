#include "manager.h"

#ifdef _WIN32
#define CLEAR "cls"
#else 
#define CLEAR "clear"
#endif

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
                //Dziala
                log_in();
                break;
            }
            case 2:
            {   
                //dziala
                system(CLEAR);
                read_users();
                std::cout << "Podaj login : " ;
                std::cin >> login ;
                std::cout << "Podaj haslo : ";
                std::cin >> password;
                auto can_can = logs.find(login);
                try{
                    if(can_can == logs.end()){//czy nie istnieje juz taki login
                        logs[login] = password;
                        std::cout << "Utworzono konto." << std::endl;
                        over_write();
                    }else
                        throw "Podany login istnieje" ;
                }catch(const char* exception){
                    std::cout << exception << std::endl;
                }
                break;
            }
            case 3:
            {
                //Dziala
                system(CLEAR);
                std::cout << "Bye" << std::endl;
                return;
                break;
            }
            default:
            {
                system(CLEAR);
                std::cout << "Wrong action !" << std::endl;
                break;
            }
        }
    }
}
void Manager::create_account(){
    system(CLEAR);
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
void Manager::read_users(std::string sciezka){
    //wpisanie do mapy zeby dola rade szukac istniejace loginy
    plik.open(sciezka,std::ios::out);
    int nr_linii = 1;
    while(std::getline(plik,napis)){
        //zczytywanie pliku
        switch(nr_linii){
            case 1:
                domain = napis;
                break;
            case 0:
                password = napis;
                logs[domain] = password;
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
void Manager::over_write(std::string sciezka){
    //nadpisywanie uzytkownikow 
    plik2.open(sciezka,std::ios::trunc);
    auto can_can = logs.begin();
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
    system(CLEAR);
    std::cout << "Podaj swoj login : ";
    std::cin >> login;
    std::cout << "Podaj haslo : ";
    std::cin >> password;
    auto check = logs.find(login);
    if(check != logs.end()){
        if(check -> second == password)
            private_account();
    }else{
        std::cout << "Nie poprawny login lub haslo." << std::endl;
        start_screen();
    }
}
std::string Manager::get_login(){
    return login;
}
void Manager::private_account(){
    system(CLEAR);
    int choose{};
    std::cout << "Udane logowanie !" << std::endl;
    while(1){
        std::cout << "---Welcome back---" << std::endl;
        std::cout << "1. Generate new password." << std::endl;
        std::cout << "2. Show my logs." << std::endl;
        std::cout << "3. Log out." << std::endl;
        std::cin >> choose;
        switch(choose){
            case 1:
                generate_pass();
                break;
            case 2:
                show_my_info();
                break;
            case 3:
                return;
                break;
            default:
                std::cout << "Wrong action." << std::endl;
                break;
        }
    }
}
void Manager::show_my_info(){
    //zczytuje osobisty plik z haslami i witrynami
    logs.clear();
    read_users("hasla\\"+login+".txt");
    system(CLEAR);
    std::cout << "---------------" << std::endl;
    for(auto a : logs){
        std::cout << "[ Witryna : " << a.first << ", Haslo : " << a.second << " ]" << std::endl;
        std::cout << "---------------" << std::endl;
    }
    system("pause");
    system(CLEAR);
}
void Manager::generate_pass(){
    std::string domena{};
    std::random_device rd;
    std::uniform_int_distribution<int> distribution{33,127};//zgodnie z tablica ascii
    std::cout << "Podaj witryne do ktorej chcesz utworzyc nowe haslo." ;
    std::cin >> domena;
    distribution(rd);
    //wyczyscic mape i wpisac do niej dane poprzednie z pliku
    logs.clear();
    read_users("hasla\\"+login+".txt");
    for(int i = 0 ; i < MAX_PASS_LEN; i++){
        pass[i] = static_cast<char>(distribution(rd));
    }
    logs[domena] = pass;
    over_write("hasla\\"+login+".txt");
}