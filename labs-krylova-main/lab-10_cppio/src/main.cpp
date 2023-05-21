#include "employees.h"
#include <iostream>

int main(){
    Employee::EmployeesArray arr;
    std::string str;
    while(std::cin>>str){
        if (str == "exit"){
            break;
        }else if (str == "load"){
            std::string file_name;
            std::cin >> file_name;
            std::ifstream file(file_name, std::ios::binary | std::ios::in);
            file >> arr;
            file.close();
        }else if (str == "save"){
            std::string file_name;
            std::cin >> file_name;
            std::ofstream file(file_name, std::ios::binary | std::ios::out);
            file << arr;
            file.close();
        }else if (str == "add"){
            std::cin >> arr;
        }else if (str == "list"){
            std::cout << arr << std::endl;
        }else{
            std::cout << "Command ifn't correct." << std::endl;
        }
    }
}

