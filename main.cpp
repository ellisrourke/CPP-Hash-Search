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

void displaySubjectGrade(std::unordered_map<nameSub,int,hashFunc> &students,std::set<std::pair<std::string,std::string>> &indirect, std::set<std::pair<std::string,std::string>>::iterator &nameItr,int choice,int threshold){
    nameItr = indirect.begin();
    advance(nameItr,choice);
    for (;nameItr != indirect.end();){
        if(nameItr != indirect.end()) {
            int grade = students[std::make_pair(nameItr->first, nameItr->second)];
            if(grade >= threshold) {
                std::cout << nameItr->first << " " << nameItr->second << " " << grade << std::endl;
            }
            advance(nameItr, 4);
        }
    }
}

void dispalyTotalMarks(std::unordered_map<nameSub,int,hashFunc> &students,std::set<std::pair<std::string,std::string>> &nameIndirect, std::set<std::pair<std::string,std::string>>::iterator &setItr,int threshold){
    //std::vector data;
    std::vector<std::pair<int,std::string>> studentsByGrade;
    auto itr = nameIndirect.begin();
    while(itr != nameIndirect.end()) {
        const std::string &name = std::get<0>(*itr);
        int sumGrades = 0;
        for (int i = 0; i < 4; i++) {
            sumGrades += students[std::make_pair(itr->first,itr->second)];
            //std::cout << std::get<0>(*itr) << " " << std::get<1>(*itr) << " " << std::get<2>(*itr) << std::endl;
            std::advance(itr, 1);
        }
        if(sumGrades>=threshold)
            std::cout << name << " " << sumGrades << std::endl;
}
}
    int main() {
        //hash table to store student grades
        std::unordered_map<nameSub, int, hashFunc> students;

        //indirect sets to allow sorting of data without modification of origional data stucture
        std::set<std::pair<std::string, std::string>> nameIndirect;
        std::set<std::tuple<int, std::string, std::string>> gradeIndirect;

        //data structure iterators
        std::unordered_map<nameSub, int, hashFunc>::iterator itr;
        std::set<std::tuple<int, std::string, std::string>>::iterator gradeItr;
        std::set<std::pair<std::string, std::string>>::iterator setItr;

        //file setup
        std::string line;
        std::ifstream infile("data.txt");

        //temp variables
        std::string name;
        std::string subject;
        int grade;

        //loop to get input student records from the file
        while (infile >> name >> subject >> grade) {
            //students[nameSub("Ellis","Mathematics")] = 67;
            students[nameSub(name, subject)] = grade;
            nameIndirect.emplace(name, subject);
            gradeIndirect.emplace(grade, name, subject);
        }
        std::cout << "1: Display Students sorted by name\n2: Display students sorted bu grade\n3: display total marks";
        std::cout << "\n4: Display total marks above threshold\n5: Display student marks for subject\n6: Display student marks for subject above threshold";
        std::cout << "\n7: Check if student exists\n8: Display all grades for a student\n";
        int select = 0;
        while(select != -1){
            std::cout << "Enter selection -> ";
            std::cin >> select;

            switch(select){
                case 1 : {//display students by name
                    std::cout << "--------------------------" << std::endl;
                    displayByName(students,nameIndirect,setItr);
                    std::cout << "--------------------------" << std::endl;

                    break;
                }
                case 2 : {//display students by grade
                    std::cout << "--------------------------" << std::endl;
                    displayByGrade(students,gradeIndirect,gradeItr);
                    std::cout << "--------------------------" << std::endl;

                    break;
                }
                case 3 : {//display total marks for each student
                    std::cout << "--------------------------" << std::endl;
                    dispalyTotalMarks(students, nameIndirect, setItr,0);
                    std::cout << "--------------------------" << std::endl;
                    break;
                }
                case 4 : {//display total marks for each student above threshold
                    int threshold;
                    std::cout << "--------------------------" << std::endl;
                    std::cout << "Enter threshold ->  ";
                    std::cin >> threshold;
                    dispalyTotalMarks(students, nameIndirect, setItr,threshold);
                    std::cout << "--------------------------" << std::endl;

                    break;
                }
                case 5 : {//display student marks for certain subject
                    std::cout << "--------------------------" << std::endl;
                    std::cout << "Select Subject\n1: Biology\n2: Chemistry\n3: Mathematics\n4: Physics\n";
                    int selection;
                    std::cin >> selection;
                    displaySubjectGrade(students, nameIndirect, setItr, selection-1,0);
                    std::cout << "--------------------------" << std::endl;

                    break;
                }
                case 6 : {//display student marks for certain subject above threshold
                    std::cout << "--------------------------" << std::endl;
                    std::cout << "Select Subject\n1: Biology\n2: Chemistry\n3: Mathematics\n4: Physics\n";
                    int selection;
                    int threshold;
                    std::cin >> selection;
                    std::cout << "Enter threshold -> ";
                    std::cin >> threshold;
                    displaySubjectGrade(students, nameIndirect, setItr, selection-1,threshold);
                    std::cout << "--------------------------" << std::endl;
                    break;
                }
                case 7 : {//check if student exists
                    std::cout << "--------------------------" << std::endl;
                    std::cout << "Enter students name -> ";
                    std::string searchStudent;
                    std::cin >> searchStudent;

                    checkRecord(students,nameIndirect,gradeIndirect,searchStudent);
                    std::cout << "--------------------------" << std::endl;

                    break;
                }
                case 8 : {//display all a single students grades
                    std::cout << "--------------------------" << std::endl;
                    std::cout << "Enter students name -> ";
                    std::string searchStudent;
                    std::cin >> searchStudent;

                    displayStudent(students,nameIndirect,searchStudent,setItr);
                    std::cout << "--------------------------" << std::endl;

                    break;
                }
                default:{
                    break;
                }


            }
        }
        //displayByName(students,nameIndirect,setItr);
        //displayByGrade(students,gradeIndirect,gradeItr);
        //checkRecord(std::unordered_map<nameSub,int,hashFunc> &students,std::set<std::pair<std::string,std::string>> &nameIndirect,std::set<std::tuple<int,std::string,std::string>> &gradeIndirect,std::string &name){
        //checkRecord(students,nameIndirect,gradeIndirect,searchStudent);
        //displayByName(students,nameIndirect,setItr);
        //displaySubjectGrade(students, nameIndirect, setItr, 3,93);
        //dispalyTotalMarks(students, nameIndirect, setItr,0);
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



//= menu