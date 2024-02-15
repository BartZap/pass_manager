#include "manager.h"
#include "encrypt.h"
#include "decrypt.h"
#ifdef _WIN32
#define CLEAR "cls"
#define CONSOLE system("pause")
#else 
#define CLEAR "clear"
#endif

Manager::Manager() = default;
Manager::~Manager() = default;
void Manager::start_screen(){
    bool steer = true;
    char choice{};
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
            case '1':
            {
                //Dziala
                log_in();
                break;
            }
            case '2':
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
            case '3':
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
                cipher(domain, std::size(domain), 0);
                break;
            case 0:
                password = napis;
                cipher(password, std::size(password), 0);
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
        std::string ov_log = can_can -> first; 
        std::string ov_pass = can_can -> second;
        cipher(ov_log, std::size(ov_log), 1);
        cipher(ov_pass, std::size(ov_pass), 1);
        plik2 << ov_log;
        plik2 << "\n";
        plik2 << ov_pass;
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
    password.clear();
    char one{};
    //nie konczy sie wpisywanie nawet enterem :/
    while(true)
    {
        one = _getwch();
        if(one == 13)
            break;
        password.push_back(one);
        std::cout << "*";
    }
    std::cout << "\n";
    auto check = logs.find(login);
    if(check != logs.end()){
        if(check -> second == password)
            private_account();
        else
            std::cout << "Nie poprawny login lub haslo." << std::endl;
    }
    else
        std::cout << "Nie poprawny login lub haslo." << std::endl;
    
}
std::string Manager::get_login(){
    return login;
}
void Manager::private_account(){
    system(CLEAR);
    char choose{};
    std::cout << "Udane logowanie !" << std::endl;
    while(1){
        std::cout << "---Welcome back---" << std::endl;
        std::cout << "1. Generate new password." << std::endl;
        std::cout << "2. Show my logs." << std::endl;
        std::cout << "3. Delete password." << std::endl;
        std::cout << "4. Log out." << std::endl;
        std::cin >> choose;
        switch(choose){
            case '1':
                generate_pass();
                break;
            case '2':
                show_my_info();
                break;
            case '3':
                delete_pass();
                break;    
            case '4':
                system(CLEAR);
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
    //std::string sciezka = to_string(path);
    read_users("./hasla/"+login+".txt");
    system(CLEAR);
    std::cout << "---------------" << std::endl;
    for(auto a = logs.begin(); a != logs.end(); a++){
        std::cout << "[ Witryna : " << a -> first << ", Haslo : " << a -> second << " ]" << std::endl;
        std::cout << "---------------" << std::endl;
    }
    //CONSOLE;
    bool mem_check = false;
    std::cout << "Press any key to continue..." << std::endl;
    std::cin.ignore();
    while(!mem_check)
    {    
        if(std::cin.get())
            mem_check = true;
    }
    system(CLEAR);
}
void Manager::generate_pass(){
    std::string domena{};
    std::random_device rd;
    std::uniform_int_distribution<int> distribution{33,127};//zgodnie z tablica ascii
    std::cout << "Podaj witryne do ktorej chcesz utworzyc nowe haslo."  << std::endl;
    std::cin >> domena;
    distribution(rd);
    //wyczyscic mape i wpisac do niej dane poprzednie z pliku
    logs.clear();
    
    read_users("./hasla/"+login+".txt");
    for(int i = 0 ; i < MAX_PASS_LEN; i++){
        pass[i] = static_cast<char>(distribution(rd));
    }
    logs[domena] = pass;
    over_write("./hasla/"+login+".txt");
}
void Manager::delete_pass()
{
    std::string domain{};
    system(CLEAR);
    logs.clear();
    std::cout << "Z jakiej domeny chcesz usunac haslo: ";
    std::cin >> domain;
    int check{};
    std::string helper{};
    read_users("./hasla/"+login+".txt");
    auto erase = logs.find(domain);
    if(erase != logs.end())
    {
        logs.erase(erase);
        over_write("./hasla/"+login+".txt");
        std::cout << "Successfully deleted password !" << std::endl;
    }
    else
        std::cout << "Check provided domain, can't find it in your password manager." << std::endl;
    bool mem_check = false;
    std::cout << "Press any key to continue..." << std::endl;
    std::cin.ignore();
    while(!mem_check)
    {    
        if(std::cin.get())
            mem_check = true;
    }
    system(CLEAR);
}
std::string Manager::cipher(std::string& c_mem, size_t c_size, bool c_truth)
{
    if(c_truth) // szyfrowanie
    {    
        for(int i = 0; i < c_size; i++)
        {
            c_mem[i] = encrypt(c_mem[i]);
        }
    }
    else    // deszyfrowanie
    {
        for(int i = 0; i < c_size; i++)
        {
            c_mem[i] = decrypt(c_mem[i]);
        }
    }
    return c_mem;
}