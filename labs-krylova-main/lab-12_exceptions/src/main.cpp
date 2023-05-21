#include <iostream>
#include "matrix.h"


int main(){
    Matrix::Registers list;
    std::string str;
    while (std::cin >> str){
        try{
            if (str == "load"){
                std::string reg, fname;
                std::cin >> reg >> fname;
                list.load(reg, fname);
            }else if (str == "print"){
                std::string reg;
                std::cin >> reg;
                list.print(reg);
            }else if (str == "add"){
                std::string reg1, reg2;
                std::cin >> reg1 >> reg2;
                list.add(reg1, reg2);
            }else if (str == "mul"){
                std::string reg1, reg2;
                std::cin >> reg1 >> reg2;
                list.mul(reg1, reg2);
            }else if( str == "elem"){
                std::string reg;
                int row, cow;
                std::cin >> reg >> row >> cow;
                std::cout << list.elem(reg,row,cow) << std::endl;

            }else if (str == "exit"){
                break;
            }else{
                std::cout << "Unexpected command" << std::endl;
            }
        }
        catch (const Matrix::MatrixException &exception){
            std::cout << exception.what() << std::endl;

        }
    }
}