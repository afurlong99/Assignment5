#include "Faculty.h"
//constructor
Faculty::Faculty() {
//defaults
    facultyID = 0;
    name = "Default";
    level = "Default";
    department = "Default";
}
//overloaded constructor
Faculty::Faculty(int fID, list<int> aID, string n, string l, string d) {
    facultyID = fID;
    advisees = aID;
    name = n;
    level = l;
    department = d;
}
//destructor
Faculty::~Faculty() {

}
//printing basic info
void Faculty::printInfo() {
    cout << "FacultyID: " << facultyID << endl;
    cout << "Advisees' ID: " << flush;
    int adviseeCount = 0;
    for (int val : advisees)
    {
        if (adviseeCount > 0)
        {
            cout << ", " << flush;
        }
        cout << val << flush;
        adviseeCount++;
    }
    cout << endl << "Name: " << name << endl;
    cout << "Level: " << level << endl;
    cout << "Department: " << department << endl << endl;
}

//tree functionalities
bool Faculty::operator < (Faculty &other) {
    return (facultyID < other.facultyID);
}

bool Faculty::operator > (Faculty &other) {
    return (facultyID < other.facultyID);
}

bool Faculty::operator == (Faculty &other) {
    return (facultyID < other.facultyID);
}

int Faculty::getID() {
    return facultyID;
}

void Faculty::addStudent(int studentID){
    advisees.push_front(studentID);
}

void Faculty::removeStudent(int studentID){
    advisees.remove(studentID);
}
