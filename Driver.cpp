#include <iostream>
#include <fstream>
#include<sstream>
#include "BST.h"
#include "TreeNode.h"
#include "Student.h"
#include "Faculty.h"
#include <stack>
#include <vector>


using namespace std;
//class functionality
void appDriver();
void displayMenu();
void readFromFiles(BST<Student>* studBst, bool* studFileFound, BST<Faculty>* facBST, bool* facFileFound);
void writeToFiles(BST<Student>* studBST, BST<Faculty>* facBST);
//creating the faculty and student stacks
stack<Student> studentStack;
stack<Faculty> facultyStack;
//bool is for true for add operations and false for delete operations
stack<bool> studentOperationsStack;
//bool is for true for add operations and false for delete operations
stack<bool> facultyOperationsStack;
//bool is for true for add student and false for faculty operations
stack<bool> lastOperationStack;

//Menu interface
void displayMenu() {
	cout << "~~~~~~~~~~~~~~~ MENU ~~~~~~~~~~~~~~~" << endl;
	cout << " 1) Print all students and their information (sorted by ascending id #)" << endl;
	cout << " 2) Print all faculty and their information (sorted by ascending id #)" << endl;
	cout << " 3) Find and display student information given the students id" << endl;
	cout << " 4) Find and display faculty information given the faculty id" << endl;
	cout << " 5) Given a student's id, print the name and info of their faculty advisor" << endl;
	cout << " 6) Given a faculty id, print ALL the names and info of his/her advisees" << endl;
	cout << " 7) Add a new student" << endl;
	cout << " 8) Delete a student given the id" << endl;
	cout << " 9) Add a new faculty member" << endl;
	cout << " 10) Delete a faculty member given the id" << endl;
	cout << " 11) Change a student's advisor given the student id and the new faculty id" << endl;
	cout << " 12) Remove an advisee from a faculty member given the ids" << endl;
	cout << " 13) Rollback" << endl;
	cout << " 14) Exit" << endl;
	cout << " 15) Commit" << endl;
}
//Core functionality for entire program(case checker)
void appDriver()
{
	BST<Student> studentBST = BST<Student>();
	BST<Faculty> facultyBST = BST<Faculty>();
	bool studentFileFound = false;
	bool facultyFileFound = false;
	readFromFiles(&studentBST, &studentFileFound, &facultyBST, &facultyFileFound);
	if (!studentFileFound)
	{
//Custom DataBace for existing student implamented if no file given
		Student Trenton(1, 1, 1, "Trenton", "Junior", "Computer Science");
		Student Other(3, 1, 3, "Other", "Sophomore", "English");
		Student Ryan(2, 2, 2, "Ryan", "Freshman", "Science");
		studentBST.insert(Trenton);
		studentBST.insert(Other);
		studentBST.insert(Ryan);
	}
	if (!facultyFileFound)
	{
//Custom DataBace for existing faculty implamented if no file given
		Faculty ProfTrent(1, list<int>(), "Professor Trent", "Professor", "Computer Science");
		Faculty ProfOther(3, list<int>(), "Professor Other", "Assoc. Prof", "Liberal Arts");
		Faculty ProfRyan(2, list<int>(), "Professor Ryan", "TA", "Engineering");
		facultyBST.insert(ProfTrent);
		facultyBST.insert(ProfOther);
		facultyBST.insert(ProfRyan);
	}
//New student and faculty varibels
	int userSelection;
	int inputID = -1;
	bool exit = false;
	int newId;
	int newAdvisorId;
	string newName;
	string newLevel;
	string newMajor;
	double newGPA;
	string newDepartment;
	list<int> forFacultyDelete;
	bool validInput = false;
	Student newStudent;
	Faculty newFaculty;

	bool operation;
//keeps the program going while the user hasn't quit
	while (!exit)
	{
// Flushes the stream to ensure proper clear screen
		cout << flush;
// Prints the menu associated with the database object db
		displayMenu();
//Receive selection from the user
		cin >> userSelection;
//All case checkers
		switch (userSelection)
		{
//Print students
		case 1:
			studentBST.printAscending(studentBST.getRoot());
			break;
//Print faculty
		case 2:
			facultyBST.printAscending(facultyBST.getRoot());

			break;
//finding Student
  	case 3:
			cout << "Please enter Student ID:" << endl;
			cin >> inputID;
			if (studentBST.callContains(inputID)) {
				studentBST.getTargetNode()->printInfo();
			}
			else {
				cout << "Student not found!" << endl;
			}
			break;
//finding Faculty
  	case 4:

			cout << "Please enter Faculty ID:" << endl;
			cin >> inputID;
			if (facultyBST.callContains(inputID)) {
				facultyBST.getTargetNode()->printInfo();
			}
			else {
				cout << "Faculty not found!" << endl;
			}
			break;
//getStudentAdvisers
		case 5:
			cout << "Please enter Student ID:" << endl;
			cin >> inputID;
			if (studentBST.callContains(inputID)) {
				if(facultyBST.callContains(studentBST.getTargetNode()->data.getAdvisorID())){
				  facultyBST.getTargetNode()->printInfo();
				}
				else{
				   cout << "Advisor not found!" << endl;
				}
			}
			else {
				cout << "Student not found!" << endl;
			}


			break;
//getFacultyAdvisees
		case 6:
			cout << "Please enter Faculty ID: " << flush;
			cin >> inputID;

			if (facultyBST.callContains(inputID))
			{
				for (int val : facultyBST.getTargetNode()->data.getStudents())
				{
					if (studentBST.callContains(val))
					{
						studentBST.getTargetNode()->printInfo();
					}
				}
			}
			break;
		case 7:
//addNewStudent
			validInput = false;

			while (!validInput)
			{
				cout << "Please enter a unique Student ID:" << endl;
				cin >> newId;
				if (studentBST.callContains(newId))
				{
					cout << "Invalid input: Student Id already in use" << endl;
				}
				else
				{
					cout << "Please enter the student's name" << endl;
					validInput = true;
				}
			}
			cin.ignore();
			getline(cin,newName);
			cout << "Please enter the student's academic year -Freshman, Sophmore, etc." << endl;
			getline(cin,newLevel);
			cout << "Please enter the student's major:" << endl;
			getline(cin,newMajor);
			cout << "Please enter student's GPA: " << endl;
			cin >> newGPA;
			validInput = false;
			while (!validInput)
			{
				cout << "Please enter an Advisor's ID:" << endl;
				cin >> newAdvisorId;
				if (!facultyBST.callContains(newAdvisorId))
				{
					cout << "Invalid input: Advisor does not exist" << endl;
				}
				else
				{
					validInput = true;
				}
			}
			newStudent.setStudentId(newId);
			newStudent.addAdvisor(newAdvisorId);
			newStudent.setGPA(newGPA);
			newStudent.setName(newName);
			newStudent.setLevel(newLevel);
			newStudent.setMajor(newMajor);

			studentBST.insert( newStudent);
			studentStack.push(newStudent);
			studentOperationsStack.push(true);
			lastOperationStack.push(true);
			facultyBST.getTargetNode()->data.addStudent(newId);
			break;
		case 8:
//deleteStudent
			validInput = false;

			while (!validInput)
			{
				cout << "Please enter the ID of the Student you wish to delete:" << endl;
				cin >> newId;
				if (!studentBST.callContains(newId))
				{
					cout << "Invalid input: Student Id does not exist" << endl;
				}
				else
				{
					studentStack.push(studentBST.getTargetNode()->data);
					studentOperationsStack.push(false);
					lastOperationStack.push(true);
					if (facultyBST.callContains(studentBST.getTargetNode()->data.getAdvisorID()))
					{
						facultyBST.getTargetNode()->data.removeStudent(newId);
					}
					validInput = true;
				}
			}
			studentBST.setRoot(studentBST.deleteNode(studentBST.getRoot(), newId));
			break;
		case 9:
			//addNewFaculty
			validInput = false;

			while (!validInput)
			{
				cout << "Please enter a unique Faculty ID:" << endl;
				cin >> newId;
				if (facultyBST.callContains(newId))
				{
					cout << "Invalid input: Faculty Id already in use" << endl;
				}
				else
				{
					cout << "Please enter the Faculty member's name" << endl;
					validInput = true;
				}
			}
			cin >> newName;
			cout << "Please enter the Faculty member's rank -Lecturer, Assoc. Professor, Professor, Dean, etc." << endl;
			cin >> newLevel;
			cout << "Please enter the Faculty member's deparment:" << endl;
			cin >> newDepartment;


			newFaculty.setFacultyId(newId);
			newFaculty.setName(newName);
			newFaculty.setLevel(newLevel);
			newFaculty.setDepartment(newDepartment);

			facultyBST.insert(newFaculty);

			facultyStack.push(newFaculty);
			facultyOperationsStack.push(true);
			lastOperationStack.push(false);
			break;
		case 10:
//deleteFaculty
			validInput = false;

			while (!validInput)
			{
				cout << "Please enter the ID of the Faculty member you wish to delete:" << endl;
				cin >> newId;
				if (!facultyBST.callContains(newId))
				{
					cout << "Invalid input: Faculty Id does not exist" << endl;
				}
				else
				{

					facultyStack.push(facultyBST.getTargetNode()->data);
					facultyOperationsStack.push(false);
					lastOperationStack.push(false);
					for (int val : facultyBST.getTargetNode()->data.getStudents())
					{
						if (studentBST.callContains(val))
						{
							studentBST.getTargetNode()->data.removeAdvisor();
						}
					}
					validInput = true;
				}

				facultyBST.setRoot(facultyBST.deleteNode(facultyBST.getRoot(), newId));
			}
			break;
		case 11:
//changeAdvisor

			validInput = false;

			while (!validInput)
			{
				cout << "Enter the id of the student you wish to reassign:" << endl;
				cin >> newId;
				if (!studentBST.callContains(newId))
				{
					cout << "Invalid input: Student not found" << endl;
				}
				else
				{
					validInput = true;
				}
			}

			validInput = false;

			while (!validInput)
			{
				cout << "Enter the id of the faculty member you wish to have this student assigned to:" << endl;
				cin >> newAdvisorId;
				if (!facultyBST.callContains(newAdvisorId))
				{
					cout << "Invalid input: Faculty member not found" << endl;
				}
				else
				{
					validInput = true;
				}
			}

			if(studentBST.getTargetNode()->data.getAdvisorID()!=newAdvisorId)
			{
				facultyBST.getTargetNode()->data.addStudent(newId);
				if (facultyBST.callContains(studentBST.getTargetNode()->data.getAdvisorID()))
				{
					facultyBST.getTargetNode()->data.removeStudent(newId);
				}
				studentBST.getTargetNode()->data.addAdvisor(newAdvisorId);
			}
			break;
		case 12:
//removeAdvisee

			validInput = false;

			while (!validInput)
			{
				cout << "Enter the id of the faculty member you wish modify:" << endl;
				cin >> newAdvisorId;
				if (!facultyBST.callContains(newAdvisorId))
				{
					cout << "Invalid input: Faculty member not found" << endl;
				}
				else
				{
					validInput = true;
				}
			}
			validInput = false;

			while (!validInput)
			{
				cout << "Enter the id of the student you wish to remove:" << endl;
				cin >> newId;
				if (!studentBST.callContains(newId))
				{
					cout << "Invalid input: Student not found" << endl;
				}
				else
				{
					validInput = true;
				}
			}
			facultyBST.getTargetNode()->data.removeStudent(newId);
			studentBST.getTargetNode()->data.removeAdvisor();
			break;
		case 13:
//rollback
			if (!lastOperationStack.empty() )
			{
				if (lastOperationStack.top())
				{
					if (studentOperationsStack.top())
					{
//delete added student
						newId = studentStack.top().getID();
							if (studentBST.callContains(newId))
							{
								if (facultyBST.callContains(studentBST.getTargetNode()->data.getAdvisorID()))
								{
									facultyBST.getTargetNode()->data.removeStudent(newId);
								}
							}
						studentBST.setRoot(studentBST.deleteNode(studentBST.getRoot(), newId));
					}
					else
					{
						studentBST.insert(studentStack.top());
					}
					studentOperationsStack.pop();
					studentStack.pop();
				}
				else
				{
					if (facultyOperationsStack.top())
					{
						newId = facultyStack.top().getID();
						if (facultyBST.callContains(newId))
						{
							for (int val : facultyBST.getTargetNode()->data.getStudents())
							{
								if (studentBST.callContains(val))
								{
									studentBST.getTargetNode()->data.removeAdvisor();
								}
							}
							validInput = true;
						}

						facultyBST.setRoot(facultyBST.deleteNode(facultyBST.getRoot(), newId));
					}
					else
					{
						facultyBST.insert(facultyStack.top());
					}
					facultyOperationsStack.pop();
					facultyStack.pop();
				}

				lastOperationStack.pop();
			}
			break;

		case 14:
			exit = true;
			cout << "exiting program..." << endl;
			break;
		case 15:
//		commit  --clears the stacks thereby preventing further rollback.  Should also print current tables back to file.
			while (!lastOperationStack.empty())
			{
				lastOperationStack.pop();
			}
			while (!studentOperationsStack.empty())
			{
				studentOperationsStack.pop();
			}
			while (!studentStack.empty())
			{
				studentStack.pop();
			}
			while (!facultyOperationsStack.empty())
			{
				facultyOperationsStack.pop();
			}
			while (!facultyStack.empty())
			{
				facultyStack.pop();
			}
			writeToFiles(&studentBST,&facultyBST);

				break;
		default:
			cout << endl << "Invalid selection..." << endl;

			break;
		}
	}
}
//Reading in from file
void readFromFiles(BST<Student>* studBST, bool* studFileFound, BST<Faculty>* facBST, bool* facFileFound) {
	string line;
	string facLine;


	string substr;

	vector<string> studAttributes;
	vector<string> facAttributes;
	ifstream readFile1("studentTable.txt");
	if (readFile1.is_open())
	{
		while (getline(readFile1, line))
		{
			Student newStudent;
			stringstream nodeStream(line);
			while (nodeStream.good())
			{
				getline(nodeStream, substr, ',');
				studAttributes.push_back(substr);
			}
//Setting file varibels for students
			newStudent.setStudentId(stoi(studAttributes[0]));
			newStudent.addAdvisor(stoi(studAttributes[1]));
			newStudent.setGPA(stod(studAttributes[2]));
			newStudent.setName(studAttributes[3]);
			newStudent.setLevel(studAttributes[4]);
			newStudent.setMajor(studAttributes[5]);

			studBST->insert(newStudent);
 			 studAttributes.clear();
		}
		readFile1.close();
		*studFileFound = true;
	}

	else cout << "Unable to open student file";
	ifstream readFile2("facultyTable.txt");
	if (readFile2.is_open())
	{
		while (getline(readFile2, facLine))
		{
			Faculty newFaculty;
			stringstream facNodeStream(facLine);
			while (facNodeStream.good())
			{
				getline(facNodeStream, substr, ',');
				facAttributes.push_back(substr);
			}
//Setting file varibels for faculty
			newFaculty.setFacultyId(stoi(facAttributes[0]));
			newFaculty.setName(facAttributes[1]);
			newFaculty.setLevel(facAttributes[2]);
			newFaculty.setDepartment(facAttributes[3]);
			for (int i = 4; i < facAttributes.size(); i++)
			{
				newFaculty.addStudent(stoi(facAttributes[i]));
			}
			facBST->insert(newFaculty);
			facAttributes.clear();
		}
		*facFileFound = true;
		readFile2.close();
	}

	else { cout << "Unable to open faculty file"; }
}
//Writing to file
void writeToFiles(BST<Student>* studBST, BST<Faculty>* facBST) {
	string line;
	stringstream nodeStream;
	string substr;
	Student newStudent;
	vector<string> attributes;
	ofstream writeFile1("studentTable.txt");
	if (writeFile1.is_open())
	{
		studBST->printTree(&writeFile1, studBST->getRoot());
		writeFile1.close();
	}
	ofstream writeFile2("facultyTable.txt");
	if (writeFile2.is_open())
	{
		facBST->printTree(&writeFile2, facBST->getRoot());
		writeFile2.close();
	}
	else cout << "Unable to open faculty file";
}
