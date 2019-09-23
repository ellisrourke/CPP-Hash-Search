//
// Created by Ellis on 23/09/2019.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>



int main(){

    std::map<std::pair<std::string,std::string>, int> students;
    students.insert(std::make_pair(std::make_pair("Ellis", "Mathematics"),98));
    std::map<std::pair<std::string,std::string>, int>::iterator itr;

    std::string line;
    std::stringstream test;
    std::string word;
    while (std::getline(std::cin, line)) {
        //std::cout << line << std::endl;

        std::string name;
        std::string subject;
        int grade;

        std::cout << name << subject << grade << std::endl;
        students.insert(std::make_pair(std::make_pair(name, subject),grade));

    }

    //std::map<std::string,std::string> students;
    //gquiz1.insert(pair<int, int>(1, 40));
    //students.insert(std::pair<std::string, std::string>("b", "a"));
    //std::map<std::string, std::string>::iterator itr;



    for (itr = students.begin(); itr != students.end(); ++itr) {
       std::cout  << itr->first.first << "\t" <<  itr->first.second << "\t" << itr->second << "\t" << std::endl;
    }
    std::cout << std::endl;




}
