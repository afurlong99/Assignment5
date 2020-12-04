#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
private:
    int advisorID;
    double gpa;
    string name;
    string level;   //freshman sophomore etc.
    string major;

public:
    int studentID;
    Student();  //defaults
    Student(int sID, int aID, double g, string n, string l, string m);  //all inputs
    ~Student();
    void printInfo();
    int getAdvisorID();
    bool operator < (Student &other);
    bool operator > (Student &other);
    bool operator == (Student &other);
    int getID();
    void addAdvisor(int facultyID);
    void removeAdvisor();
    void setGPA(double inGPA) { gpa = inGPA; };
    void setStudentId(int inID) { studentID = inID; };
    void setName(string inName) { name = inName; };
    void setLevel(string inLevel) { level = inLevel; };
    void setMajor(string inMajor) { major = inMajor; };
    void printNode(ofstream* outStream);
};

#endif
