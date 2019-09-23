#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <unordered_map>
#include <chrono>
int main(){
    auto start = std::chrono::steady_clock::now();
    clock_t startClock = clock(); // record the clock at start

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
        std::cin >> name >> subject >> grade;
        //std::cout << name << subject << grade << std::endl;
        students.insert(std::make_pair(std::make_pair(name, subject),grade));
    }

    //std::map<std::string,std::string> students;
    //gquiz1.insert(pair<int, int>(1, 40));
    //students.insert(std::pair<std::string, std::string>("b", "a"));
    //std::map<std::string, std::string>::iterator itr;

    for (itr = students.begin(); itr != students.end(); ++itr) {
       std::cout  << itr->first.first  << " " <<   itr->first.second  << " " << itr->second  << std::endl;
    }
    std::cout << std::endl;

    auto end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time in milliseconds : "
         << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
         << " ms" << std::endl;









}


//                  | map             | unordered_map
//---------------------------------------------------------
//Ordering        | increasing  order   | no ordering
//                | (by default)        |
//
//Implementation  | Self balancing BST  | Hash Table
//                | like Red-Black Tree |
//
//search time     | log(n)              | O(1) -> Average
//                |                     | O(n) -> Worst Case
//
//Insertion time  | log(n) + Rebalance  | Same as search
//
//Deletion time   | log(n) + Rebalance  | Same as search
