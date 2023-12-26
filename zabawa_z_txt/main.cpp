#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

int main(){
    
    std::string napis{},login{},haslo{};
    std::ifstream plik;
    std::ofstream plik2;
    std::map<std::string,std::string> logs{};
    plik.open("napisy.txt",std::ios::out);
    int nr_linii = 1;
    while(std::getline(plik,napis)){
        //zczytywanie pliku
        switch(nr_linii){
            case 1:
                login = napis;
                break;
            case 0:
                haslo = napis;
                logs[login] = haslo;
                break;
            default:
                std::cout << "Bad file" << std::endl;
                break;
        }
        nr_linii++;
        nr_linii = nr_linii % 2;
    }
    plik.close();
    plik2.open("napisy.txt",std::ios::trunc);
    std::cout << "Podaj login : " ;
    std::cin >> login ;
    std::cout << "Podaj haslo : ";
    std::cin >> haslo;
    auto can_can = logs.find(login);
    if(can_can == logs.end())//czy nie istnieje juz taki login
        logs[login] = haslo;
    else
        std::cout << "Podany login istnieje" << std::endl;
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
    return 0;
}
