#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <chrono>
#include <array>
#include <vector>
#include "gendata.h"
#include <fstream>
typedef std::pair<std::string,std::string> nameSub;
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

class findName {
public:
    explicit findName(std::string &name) : name{name} {};

    bool operator()(const std::pair<std::string,std::string> &toFind){
        return toFind.first == this->name;
    }

    std::string name;
};

struct hashFunc{
    size_t operator()(const nameSub &test) const{
        //std::cout << (std::hash<std::string>()(test.first) * std::hash<std::string>()(test.second)) << std::endl;
        return std::hash<std::string>()(test.first) * std::hash<std::string>()(test.second);
    }
};

void displayByGrade(std::unordered_map<nameSub,int,hashFunc> &students,std::set<std::tuple<int,std::string,std::string>> &gradeIndirect, std::set<std::tuple<int,std::string,std::string>>::iterator &gradeItr){
    for (gradeItr = gradeIndirect.begin(); gradeItr != gradeIndirect.end(); ++gradeItr){
        std::cout  << std::get<1>(*gradeItr)  << " " <<   std::get<2>(*gradeItr)  << " "  << students[std::make_pair(std::get<1>(*gradeItr),std::get<2>(*gradeItr))] << std::endl;
    }
}

void displayByName(std::unordered_map<nameSub,int,hashFunc> &students,std::set<std::pair<std::string,std::string>> &nameIndirect, std::set<std::pair<std::string,std::string>>::iterator &setItr){
    for (setItr = nameIndirect.begin(); setItr != nameIndirect.end(); ++setItr){
        std::cout  << setItr->first  << " " <<   setItr->second  << " "  << students[std::make_pair(setItr->first,setItr->second)] << std::endl;
    }
}

void checkRecord(std::unordered_map<nameSub,int,hashFunc> &students,std::set<std::pair<std::string,std::string>> &nameIndirect,std::set<std::tuple<int,std::string,std::string>> &gradeIndirect,std::string &name){
    std::string m = "Biology";
    if(!students[nameSub(name,m)]){
        std::cout << "Does not exist... add? -> (y/n)";
        char option;
        std::cin >> option;
        if(option=='y'){
            int g;
            std::string subs[4] = {"Biology","Chemistry","Mathematics","Physics"};
            for(const auto & sub : subjects){
                std::cout << "grade for " << sub << "->";
                std::cin >> g;
                students[nameSub(name,sub)] = g;
                nameIndirect.emplace(name,sub);
                gradeIndirect.emplace(g,name,sub);
            }
        }
    } else {
        std::cout << "Record exists in data"  ;
    }
}

void displayStudent(std::unordered_map<nameSub,int,hashFunc> &students,std::set<std::pair<std::string,std::string>> &nameIndirect,std::string &name,std::set<std::pair<std::string,std::string>>::iterator &setItr){
    auto itr = std::find_if(nameIndirect.begin(), nameIndirect.end(),findName(name));
    std::string subs[] = {"Biology","Chemistry","Mathematics","Physics"};
    std::string m = "Biology";
    for(auto & sub : subs){
        std::cout << name << " " << sub << " " << students[std::make_pair(name,sub)] << std::endl;
    }
}

void displaySubjectGrade(std::unordered_map<nameSub,int,hashFunc> &students,std::set<std::pair<std::string,std::string>> &indirect, std::set<std::pair<std::string,std::string>>::iterator &nameItr,int choice){
    nameItr = indirect.begin();
    advance(nameItr,choice);
    for (;nameItr != indirect.end();){
        if(nameItr != indirect.end()) {
            std::cout << nameItr->first << " " << nameItr->second << " " << students[std::make_pair(nameItr->first, nameItr->second)] << std::endl;
            advance(nameItr, 4);
        }
    }
}

void dispalyTotalMarks(std::unordered_map<nameSub,int,hashFunc> &students,std::set<std::pair<std::string,std::string>> &nameIndirect, std::set<std::pair<std::string,std::string>>::iterator &setItr){
    //std::vector data;
    std::vector<std::pair<int,std::string>> studentsByGrade;
    auto itr = nameIndirect.begin();
    while(itr != nameIndirect.end()) {
        const std::string &name = std::get<0>(*itr);
        std::cout << name << " ";
        int sumGrades = 0;
        for (int i = 0; i < 4; i++) {
            sumGrades += students[std::make_pair(itr->first,itr->second)];
            //std::cout << std::get<0>(*itr) << " " << std::get<1>(*itr) << " " << std::get<2>(*itr) << std::endl;
            std::advance(itr, 1);
        }
        std::cout << sumGrades << std::endl;
}
}
    int main() {
        std::unordered_map<nameSub, int, hashFunc> students;
        std::unordered_map<nameSub, int, hashFunc>::iterator itr;
        std::set<std::pair<std::string, std::string>> nameIndirect;
        std::set<std::tuple<int, std::string, std::string>> gradeIndirect;
        std::set<std::tuple<int, std::string, std::string>>::iterator gradeItr;
        std::set<std::pair<std::string, std::string>>::iterator setItr;


        std::string line;
        std::ifstream infile("data.txt");

        std::string name;
        std::string subject;
        int grade;

        while (infile >> name >> subject >> grade) {
            //students[nameSub("Ellis","Mathematics")] = 67;
            students[nameSub(name, subject)] = grade;
            nameIndirect.emplace(name, subject);
            gradeIndirect.emplace(grade, name, subject);
        }

        //displayByName(students,nameIndirect,setItr);
        std::cout << "====================================================" << std::endl;
        //displayByGrade(students,gradeIndirect,gradeItr);

        //checkRecord(std::unordered_map<nameSub,int,hashFunc> &students,std::set<std::pair<std::string,std::string>> &nameIndirect,std::set<std::tuple<int,std::string,std::string>> &gradeIndirect,std::string &name){
        std::string searchStudent = "Zoe";
        //checkRecord(students,nameIndirect,gradeIndirect,searchStudent);
        //displayByName(students,nameIndirect,setItr);
        std::cout << "====================================================" << std::endl;

        //displaySubjectGrade(students, nameIndirect, setItr, 3);
        //void displaySubjectGrade(std::unordered_map<nameSub,int,hashFunc> &students,std::set<std::tuple<int,std::string,std::string>> &gradeIndirect, std::set<std::tuple<int,std::string,std::string>>::iterator &gradeItr){

        dispalyTotalMarks(students, nameIndirect, setItr);


        //std::unordered_map<nameSub,int,hashFunc> &students,std::set<std::pair<std::string,std::string>> &nameIndirect, std::set<std::pair<std::string,std::string>>::iterator &setItr

    }


//unordered_map
//---------------------------------------------------------
//Ordering        | no ordering
//
//search time     | O(1) -> Average
//                | O(n) -> Worst Case
//
//Insertion time  | O(1) -> Average
////              | O(n) -> Worst Case
//
//Deletion time   | O(1) -> Average
////              | O(n) -> Worst Case


//TO ADD
//= sort by total marks
//= how many students have obtained more than a given marks in a particular subject or in total marks