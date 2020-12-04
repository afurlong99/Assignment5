#include "Student.h"

//constructor
Student::Student() {
    studentID = -1;
    advisorID = -1;
    gpa = -1.0;
}
//overloaded constructor
Student::Student(int sID, int aID, double g, string n, string l, string m) {
    studentID = sID;
    advisorID = aID;
    gpa = g;
    name = n;
    level = l;
    major = m;
}
//destructor
Student::~Student() {
}
//print info function
void Student::printInfo() {
    cout << "Student ID: " << studentID << endl;
    if (advisorID < 0){
      cout << "Advisor ID: -UNASSIGNED- "<< endl;
    }
    cout << "Advisor ID: " << advisorID << endl;
    cout << "Name: " << name << endl;
    cout << "GPA: " << gpa << endl;
    cout << "Grade Level: " << level <<endl;
    cout << "Major: " << major << endl << endl;
}
//operators for tree functionality

bool Student::operator < (Student &other) {
    return (studentID < other.studentID);
}

bool Student::operator > (Student &other) {
    return (studentID > other.studentID);
}

bool Student::operator == (Student &other) {
    return (studentID == other.studentID);
}

//basic getters
int Student::getID(){
  return studentID;
}

int Student::getAdvisorID(){
  return advisorID;
}
//basic setter
void Student::addAdvisor(int facultyID){
  advisorID = facultyID;
}

void Student::removeAdvisor(){
  advisorID = -1;
}
//function for printing out to file
void Student::printNode(ofstream* outStream)
{
    cout << "Writing the following to file " << flush;
    cout << studentID << "," << flush;
    cout << advisorID << "," << flush;
    cout << gpa << "," << flush;
    cout << name << "," << flush;
    cout << level << "," << flush;
    cout << major << endl;
    *outStream << studentID << "," << advisorID << "," << gpa << "," << name << "," << level << "," << major << endl;
    cout << "written" << endl;
}
