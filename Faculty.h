#ifndef FACULTY_H
#define FACULTY_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

class Faculty {
private:
    int facultyID;
    list<int> advisees; 
    string name;
    string level;
    string department;

public:
    Faculty();
    Faculty(int fID, list<int> aID, string n, string l, string d);  //all inputs
    ~Faculty();
    void printInfo();
    bool operator < (Faculty &other);
    bool operator > (Faculty &other);
    bool operator == (Faculty &other);
    int getID();
    void addStudent(int studentID);
    void removeStudent(int studentID);
    list<int> getStudents() { return advisees; };
    void setFacultyId(int id) { facultyID = id; };
    void setName(string newName) { name = newName; };
    void setLevel(string newLevel) { level = newLevel; };
    void setDepartment(string newDepartment) { department = newDepartment; };

    void printNode(ofstream* outStream)
    {
        *outStream << facultyID << "," << name << "," << level << "," << department << flush;
        for (int val : advisees)
        {
                *outStream << "," <<val<< flush;
        }
        *outStream << endl;
    };
};

#endif
