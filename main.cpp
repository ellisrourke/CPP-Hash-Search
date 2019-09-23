//
// Created by Ellis on 23/09/2019.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>



int main(){
    std::string line;
    std::stringstream test;
    std::string word;
    while (std::getline(std::cin, line)){
        //std::cout << line << std::endl;

            std::string name;
            std::string subject;
            int grade;
            std::cin >> name >> subject >> grade;
            std::cout << name << std::endl;

    }

}
