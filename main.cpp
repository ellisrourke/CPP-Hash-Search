#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <chrono>
#include <array>
#include "gendata.h"
#include <fstream>
class compareGrades{
public:
    bool operator()(const std::tuple<std::string, std::string, int> &a, const std::tuple<std::string, std::string, int> &b)const{
        return std::get<2>(a) <= std::get<2>(b);
    }
};

class compareNames{
public:
    bool operator()(const std::tuple<std::string, std::string, int> &a, const std::tuple<std::string, std::string, int> &b) const {
        const std::string &nameA = std::get<0>(a);
        const std::string &subjectA = std::get<1>(a);
        int gradeA = std::get<2>(a);

        const std::string &nameB = std::get<0>(b);
        const std::string &subjectB = std::get<1>(b);
        int gradeB = std::get<2>(b);

        bool result;
        if (nameA < nameB) {
            return true;
        } else if (nameA == nameB){
            if (subjectA < subjectB)
                return true;
            else
                return subjectA < subjectB;
        }
        return false;
    }
};

typedef std::pair<std::string,std::string> nameSub;
struct hashFunc{
    size_t operator()(const nameSub &test) const{
        //std::cout << (std::hash<std::string>()(test.first) * std::hash<std::string>()(test.second)) << std::endl;
        return std::hash<std::string>()(test.first) * std::hash<std::string>()(test.second);
    }
};

std::string exists(std::unordered_map<nameSub,int,hashFunc> & students, std::pair<std::string, std::string>  const & ser) {
    if (students.find(ser) == students.end())
        return "Element Not Present\n";
    else
        return "Element Present\n";
}

    int main(){
    std::unordered_map<nameSub,int,hashFunc> students;
    std::unordered_map<nameSub,int,hashFunc>::iterator itr;
    std::set<std::pair<std::string,std::string>> nameIndirect;
    std::set<std::tuple<int,std::string,std::string>> gradeIndirect;
    std::set<std::tuple<int,std::string,std::string>>::iterator gradeItr;
    std::set<std::pair<std::string,std::string>>::iterator setItr;



    std::string line;
    std::ifstream infile("data.txt");

    std::string name;
    std::string subject;
    int grade;

    while (infile >> name >> subject >> grade) {
        //students[nameSub("Ellis","Mathematics")] = 67;
        students[nameSub(name,subject)] = grade;
        nameIndirect.emplace(name,subject);
        gradeIndirect.emplace(grade,name,subject);
    }


    for (setItr = nameIndirect.begin(); setItr != nameIndirect.end(); ++setItr){
       std::cout  << setItr->first  << " " <<   setItr->second  << " "  << students[std::make_pair(setItr->first,setItr->second)] << std::endl;

    }
    std::cout << "====================================================" << std::endl;
    //std::cout << students[nameSub("Ellis","Mathematics")];
    //std::cout << students[std::make_pair("Zoey","Mathematics")];
    //std::cout << exists(students,nameSub("Zoey","Physics"));
    for (gradeItr = gradeIndirect.begin(); gradeItr != gradeIndirect.end(); ++gradeItr){
        std::cout  << std::get<1>(*gradeItr)  << " " <<   std::get<2>(*gradeItr)  << " "  << students[std::make_pair(std::get<1>(*gradeItr),std::get<2>(*gradeItr))] << std::endl;

    }




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
