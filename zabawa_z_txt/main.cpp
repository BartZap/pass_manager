#include <iostream>
#include <fstream>
#include <string>
#include <map>

int main(){
    
    std::string napis{},login{},haslo{};
    std::fstream plik;
    std::map<std::string,std::string> logs{};
    plik.open("napisy.txt",std::ios::in);
    int nr_linii = 1;
    while(std::getline(plik,napis)){
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
    plik.open("napisy.txt",std::ios::out);
    std::cin >> login >> haslo;
    plik >> login;
    plik.write(login,login.lenght());
    plik >> haslo;
    plik.write(login,haslo.lenght());
    plik.flush();
    plik.close();
    return 0;
}