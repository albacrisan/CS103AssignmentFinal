// CS103Assignment2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> //for basic input and output
#include <vector>
#include <list>
#include <fstream> //for handling the files - e.g. csv etc
#include <string>
#include <Windows.h>
#include <iomanip>
#include <stdlib.h>
#include <ctime> 
#include <map>
#include <cstdlib> //for exit() and system(“cls”) functions
#include <cstring> //for all string functions
#include <conio.h> //for getch() function
#include <sstream>
using namespace std;

struct Parent {
	string fName;
	string lName;
	long int contactNumber;
	Parent(string fN = "FirstName", string lN = "LastName", long int cN = 0000000000) {
		fName = fN;
		lName = lN;
		contactNumber = cN;
	}
};
struct Teacher {
	string fName;
	string lName;
	Teacher(string fN = "FirstName", string lN = "LastName") {
		fName = fN;
		lName = lN;
	}

};
struct classStr {
	string code;
	float studentGrade;
	float courseCost;
	Teacher teacher;
	classStr(string c = "ClassCode", float sG = 0, float cC = 7000) {
		code = c;
		studentGrade = sG;
		courseCost = cC;
	}
};

struct Student { // main struct, all others are nested within student, database will hold all student and class information somehow. maybe have seperate DB for classes?
	long int ID;
	string Password;
	string fName;
	string lName;
	string email;
	Parent parent;
	classStr class1;
	classStr class2;
	classStr class3;
	classStr class4;

	Student(int id = 001122, string pw = "Password", string fN = "FirstName", string lN = "LastName", string em = "email@domain.com") {
		ID = id;
		Password = pw;
		fName = fN;
		lName = lN;
		email = em;

	}
};


// for the course info

struct CourseRecord {
public:
	CourseRecord(  //courseID, coursename, semester, YEAR, costlocal, costinternational, teacher per file
		string id,
		string courseName,
		string semester,
		int yEAR,
		double costLocal,
		double costInternational,
		string teacher

	)

	{

		Id = id; // courseID
		CourseName = courseName; // coursename
		Semester = semester; // semester
		YEAR = yEAR;
		CostLocal = costLocal;
		CostInternational = costInternational;
		Teacher = teacher;
	}


void display() {
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 10);
		cout << "Course ID and name: " << Id << " " << CourseName;
		SetConsoleTextAttribute(color, 8);
		cout << " Teacher: " << Teacher << endl;
		SetConsoleTextAttribute(color, 7);
		cout << "Year: " << YEAR << " - " << Semester << " ";
		SetConsoleTextAttribute(color, 13);
		cout << "---> Course Cost local: NZD$" << CostLocal << " and international cost: NZD$" << CostInternational << endl;
		cout << endl;
	}

	string Id;
	string CourseName;
	string Semester;
	int YEAR;
	double CostLocal;
	double CostInternational;
	string Teacher;

};

void displayCourses(vector<CourseRecord>& courses) {

	for (auto course : courses) {
		course.display();
	}
}
// course info ends




vector <Student> Registration(vector<Student>& student);
vector <Student> StudentLogin();
void adminLogin(vector<Student>& student);
void adminDatabase(vector<Student>& student);
void studentDatabase();

//admin Database menu option functions
void studentSearch(vector<Student>& student);
void printDatabase(vector<Student>& student);
void editRoll();
void gradeStudent(vector<Student>& student);

void editStudent();
void studentClassSum();
void StudentGradeSum();
void studentTuitionSum();

void ShowHeader();

void studentAvailableCourses();
void endMenuchoise();

int main() {

	ShowHeader();

	vector <Student> student;
	vector <Student> studentFromFile;
	int menuChoice, loginChoice;
	//cout << "***University Database***\n\n\n";
	cout << "Press 1 to Login\nPress 2 to Register\nPress 3 to exit Program\nEnter your choice: "; cin >> menuChoice;
	switch (menuChoice) {
	case 1:
		cout << "\n\nPress 1 for student login\nPress 2 for Admin login\nEnter your choice: "; cin >> loginChoice;
		if (loginChoice == 1) {
			cout << "\n\nDirecting to Student Login...";
			Sleep(500);
			StudentLogin();
			break;
		}
		else if (loginChoice == 2) {
			cout << "\n\nDirecting to Admin Login...";
			Sleep(500);
			adminLogin(student);
			break;
		}
		else {
			cout << "Invalid input. Press 1 or 2";
			Sleep(1000);
			system("cls");
			main();
			break;
		}
	case 2:
		cout << "\n\nDirecting to Student Registration...";
		Sleep(500);
		student = Registration(student);
		break;
	case 3:
		cout << "\n\nClosing App...";
		Sleep(500);
		exit(1);
	default:
		cout << "\n\ninvalid input. Press 1,2 or 3";
		Sleep(1000);
		system("cls");
		main();
	}


}

vector <Student> Registration(vector<Student>& student) {
	system("cls");
	ShowHeader();
	Student s;
	int IDflag = 0, PWflaglength = 0, PWflaglow = 0, PWflagHigh = 0, PWflagNum = 0, PWflagSpec = 0, passwordIndex;
	cout << "***Student Registration***\n\n";
	while (IDflag == 0) {
		cout << "Please Enter your Student ID (6 digit Number): "; cin >> s.ID;
		if (sizeof(s.ID) == 4) {
			IDflag = 1;
			break;
		}
		else {
			cout << "ID must be 6 digits long\n\n\n";
		}
	}
	while (PWflaglength == 0 && PWflaglow == 0 && PWflagHigh == 0 && PWflagNum == 0 && PWflagSpec == 0) {
		cout << "Create your password. Password must container uppercase,lowercase & number: "; cin >> s.Password;
		for (passwordIndex = 0; passwordIndex < s.Password.size(); passwordIndex++) {
			if (isdigit(s.Password[passwordIndex])) {
				PWflagNum = 1;
			}
			else {
				cout << "Password must contain atleast 1 number letter\n";
			}
		}
		for (passwordIndex = 0; passwordIndex < s.Password.size(); passwordIndex++) {
			if (islower(s.Password[passwordIndex])) {
				PWflaglow = 1;
			}
			else {
				cout << "Password must contain atleast 1 lowercase letter\n";
			}
		}
		for (passwordIndex = 0; passwordIndex < s.Password.size(); passwordIndex++) {
			if (isupper(s.Password[passwordIndex])) {
				PWflagHigh = 1;
			}
			else {
				cout << "Password must contain atleast 1 uppercase letter\n";
			}
		}
		for (passwordIndex = 0; passwordIndex < s.Password.size(); passwordIndex++) {
			if (isupper(s.Password[passwordIndex])) {
				PWflagHigh = 1;
			}
			else {
				cout << "Password must contain atleast 1 uppercase letter\n";
			}
		}
		for (passwordIndex = 0; passwordIndex < s.Password.size(); passwordIndex++) {
			if (s.Password.size() > 7){
				PWflaglength = 1;
			}
			else {
				cout << "ID must be 6 digits long\nTry again";
			}
		}
	}
	cout << "Enter your first name: "; cin >> s.fName;
	cout << "Enter your last name: "; cin >> s.lName;
	cout << "Enter you email address: "; cin >> s.email;
	cout << endl << endl;
	cout << "Emergency Contact Details\n\n";
	cout << "Enter first name: "; cin >> s.parent.fName;
	cout << "Enter last name: "; cin >> s.parent.lName;
	cout << "Enter contact number: "; cin >> s.parent.contactNumber;
	student.push_back(s);
	if (IDflag == 1, PWflaglength == 1, PWflaglow == 1, PWflagHigh == 1, PWflagNum == 1, PWflagSpec == 1) {
		fstream StudentDatabase("stDB.csv", ios::app);
		for (int i = 0; i < student.size(); i++) {

			StudentDatabase << s.ID << "," << s.Password << "," << s.fName << "," << s.lName << "," << s.email << "," << s.parent.fName << "," << s.parent.lName << "," << s.parent.contactNumber << "," << s.class1.code << "," << s.class1.studentGrade << "," << s.class1.courseCost << "," << s.class2.code << "," << s.class2.studentGrade << "," << s.class2.courseCost << "," << s.class3.code << "," << s.class3.studentGrade << "," << s.class3.courseCost << "," << s.class4.code << "," << s.class4.studentGrade << "," << s.class4.courseCost << "," << endl;

		}
		StudentDatabase.close();
		cout << "\n\nRegistration Successfull\nDirecting to main menu...";
		Sleep(1000);
		system("cls");
		main();
		return(student);
	}

}
vector <Student> StudentLogin() {
	system("cls");
	ShowHeader();
	Student s;
	string attemptPW;
	long int attemptID;
	int counter = 3, flag = 0;
	vector<Student> tempStudent;
	while (counter != 0) {
		cout << "***Student Login***\n\n";
		cout << "Enter ID: "; cin >> attemptID;
		cout << "Enter PW: "; cin >> attemptPW;
		string line;
		string property;
		fstream StudentDatabase("stDB.csv", ios::in);
		vector<Student> tempStudent;
		while (getline(StudentDatabase, line)) {
			istringstream linestream(line);
			getline(linestream, property, ',');
			stringstream ss(property);
			ss >> s.ID;
			getline(linestream, property, ',');
			s.Password = property;
			getline(linestream, property, ',');
			s.fName = property;
			getline(linestream, property, ',');
			s.lName = property;
			tempStudent.push_back(s);


			if (attemptID == s.ID && attemptPW == s.Password) {
				flag = 1;
			}
		}
		switch (flag) {
		case 0:
			counter--;
			cout << "\nIncorrect ID or Password\n" << counter << " login attempts remaining\n";
			break;

		case 1:
			cout << "\nLogin successfull. Welcome " << s.fName << " " << s.lName << "\nDirecting you to your student database...\n";
			Sleep(1000);
			studentDatabase();
			break;
		}
		StudentDatabase.close();
	}
	cout << "Closing app...\n\n\n\n";
	Sleep(1000);
	exit(1);
	return(tempStudent);
}

void adminLogin(vector<Student>& student) {
	system("cls");
	int counter = 3, flag = 0;
	long int adminID = 000000, enteredID;
	string adminPW = "Password", enteredPW;
	while (counter != 0) {
		cout << "***Admin Login***\n";
		cout << "Enter Admin ID: "; cin >> enteredID;
		cout << "Enter Admin PW: "; cin >> enteredPW;
		if (adminID == enteredID && adminPW == enteredPW) {
			flag = 1;
		}
		switch (flag) {
		case 0:
			counter--;
			cout << "\nIncorrect ID or Password\n" << counter << " login attempts remaining\n";
			break;

		case 1:
			cout << "\nLogin successfull\nDirecting you to database...\n";
			Sleep(1000);
			adminDatabase(student);
			break;
		}
	}
	cout << "Closing app...\n\n\n\n";
	Sleep(1000);
	exit(3);
}

void adminDatabase(vector<Student>& student) {
	system("cls");
	ShowHeader();
	int menuChoice;
	cout << "***Admin Database Access***\n\n";
	cout << "Press 1 to search for a student by ID number\n"; // search for student by ID which spits out student data in full if matching ID is found
	cout << "Press 2 to view student full student database\n";// prints all data in the student database
	cout << "Press 3 to edit class roles\n"; // opens options to add or remove students to class role by searching for their ID in the DB
	cout << "Press 4 to assign student grades\n"; // add or change student grade for each class
	cout << "Press 5 to log out\n"; // return to main and log out
	cout << "Enter your choice: "; cin >> menuChoice;

	switch (menuChoice) {
	case 1: studentSearch(student);
		break;
	case 2: printDatabase(student);
		break;
	case 3: editRoll();
		break;
	case 4: gradeStudent(student);
		break;
	case 5:
		cout << "\n\nLogging out\nReturning to main menu...";
		Sleep(1000);
		main();
	};
}

 void studentSearch(vector<Student>& student) { //always finds and prints the latest ID in the list -- not the line that matches the ID entered by Admin
		system("cls");
		long int IDsearch;
		cout << "Search for student by ID: "; cin >> IDsearch;
		Student s;
		char searchChoice;
		int flag = 0;
		string line;
		string property;
		ifstream StudentDatabase("stDB.csv", ios::in);
		vector<Student> tempStudent;
		Student foundStudent;
		while (getline(StudentDatabase, line)) {
			istringstream linestream(line);
			getline(linestream, property, ',');
			stringstream ss(property);
			ss >> s.ID;
			getline(linestream, property, ',');
			s.Password = property;
			getline(linestream, property, ',');
			s.fName = property;
			getline(linestream, property, ',');
			s.lName = property;
			getline(linestream, property, ',');
			s.email = property;
			getline(linestream, property, ',');
			s.parent.fName = property;
			getline(linestream, property, ',');
			s.parent.lName = property;
			getline(linestream, property, ',');
			stringstream sc(property);

			getline(linestream, property, ',');
			s.class1.code = property;
			getline(linestream, property, ',');
			stringstream aCG(property);
			aCG >> s.class1.studentGrade;
			getline(linestream, property, ',');
			stringstream aCC(property);
			aCC >> s.class1.courseCost;

			getline(linestream, property, ',');
			s.class2.code = property;
			getline(linestream, property, ',');
			stringstream bCG(property);
			bCG >> s.class2.studentGrade;
			getline(linestream, property, ',');
			stringstream bCC(property);
			bCC >> s.class2.courseCost;

			getline(linestream, property, ',');
			s.class3.code = property;
			getline(linestream, property, ',');
			stringstream cCG(property);
			cCG >> s.class3.studentGrade;
			getline(linestream, property, ',');
			stringstream cCC(property);
			cCC >> s.class3.courseCost;

			getline(linestream, property, ',');
			s.class4.code = property;
			getline(linestream, property, ',');
			stringstream dCG(property);
			dCG >> s.class4.studentGrade;
			getline(linestream, property, ',');
			stringstream dCC(property);
			dCC >> s.class4.courseCost;
			sc >> s.parent.contactNumber;
			tempStudent.push_back(s);
		}
		for (int i = 0; i < student.size(); i++) {
				if (student[i].ID == IDsearch) {
					flag = 1;
					foundStudent = s;
					break;
				}
			}
		switch (flag) {
		case 0:
			cout << "No student with ID: " << IDsearch << " was found\n";
			cout << "Search again? Y/N: "; cin >> searchChoice;
			if (searchChoice == 'y' || searchChoice == 'Y') {
				studentSearch(student);
			}
			else {
				cout << "\n Returning to Admin main menu...";
				Sleep(1000);
				adminDatabase(student);
			}
			break;
		case 1:
			cout << "\nStudent " << foundStudent.ID << " found\nFinding student data...\n\n\n";
			Sleep(1000);

			cout << "Personal Contact Details\n\n";
			cout << "Student ID: " << foundStudent.ID<< endl;
			cout << "Student Password: " << foundStudent.Password << endl;
			cout << "First Name: " << foundStudent.fName << endl;
			cout << "Last Name: " << foundStudent.lName << endl;
			cout << "Email Address: " << foundStudent.email << endl << endl;

			cout << "Emergency Contact Details\n\n";
			cout << "First Name: " << foundStudent.parent.fName << endl;
			cout << "Last Name: " << foundStudent.parent.lName << endl;
			cout << "Contact Number: " << foundStudent.parent.contactNumber << endl << endl;

			cout << "Student Grades\n\n";
			cout << "Class 1: " << foundStudent.class1.code << "\tGrade: " << foundStudent.class1.studentGrade << "%" << endl;
			cout << "Class 2: " << foundStudent.class2.code << "\tGrade: " << foundStudent.class2.studentGrade << "%" << endl;
			cout << "Class 3: " << foundStudent.class3.code << "\tGrade: " << foundStudent.class3.studentGrade << "%" << endl;
			cout << "Class 4: " << foundStudent.class4.code << "\tGrade: " << foundStudent.class4.studentGrade << "%" << endl << endl;
			
			cout << "Search again? Y/N: "; cin >> searchChoice;
			if (searchChoice == 'y' || searchChoice == 'Y') {
				studentSearch(student);
			}
			else {
				cout << "\n Returning to Admin main menu...";
				Sleep(1000);
				adminDatabase(student);
			}
			break;
		}
	}
	void printDatabase(vector<Student>& student) { //doesnt give the correct defaults for grade,coursecode or tution cost -- are these initialized anywhere?? also loops back to login as admin once its finished coding. //add intialized struct values onto DB
		cout << "Printing full Database...\n\n\n\n"; 
		Sleep(1000); 
		string line;
		Student s;
		string property;
		fstream StudentDatabase("stDB.csv", ios::in);
		vector<Student> tempStudent;
		while (getline(StudentDatabase, line)) {
			istringstream linestream(line);
			getline(linestream, property, ',');
			stringstream ss(property);
			ss >> s.ID;
			getline(linestream, property, ',');
			s.Password = property;
			getline(linestream, property, ',');
			s.fName = property;
			getline(linestream, property, ',');
			s.lName = property;
			getline(linestream, property, ',');
			s.email = property;
			getline(linestream, property, ',');
			s.parent.fName = property;
			getline(linestream, property, ',');
			s.parent.lName = property;
			getline(linestream, property, ',');
			stringstream sc(property);
			sc >> s.parent.contactNumber;
			                                                                      //if we dont try and pull from DB when there is nothing written then its fine. but what happens if there is something written?
			getline(linestream, property, ',');
			s.class1.code = property; 
			getline(linestream, property, ',');
			stringstream aCG(property); 
			aCG >> s.class1.studentGrade; 
			getline(linestream, property, ',');
			stringstream aCC(property);  
			aCC >> s.class1.courseCost; 

			getline(linestream, property, ',');
			s.class2.code = property; 
			getline(linestream, property, ',');
			stringstream bCG(property); 
			bCG >> s.class2.studentGrade; 
			getline(linestream, property, ',');
			stringstream bCC(property);
			bCC >> s.class2.courseCost;

			getline(linestream, property, ',');
			s.class3.code = property; 
			getline(linestream, property, ',');
			stringstream cCG(property);
			cCG >> s.class3.studentGrade;
			getline(linestream, property, ',');
			stringstream cCC(property);
			cCC >> s.class3.courseCost;
			
			getline(linestream, property, ',');
			s.class4.code = property; 
			getline(linestream, property, ',');
			stringstream dCG(property);
			dCG >> s.class4.studentGrade;
			getline(linestream, property, ',');
			stringstream dCC(property);
			dCC >> s.class4.courseCost;
			
			tempStudent.push_back(s);
		}
		for (int i = 0; i < tempStudent.size(); i++) { 
			cout << "Student " << tempStudent[i].ID << ":\n\n";

			cout << "Personal Contact Details: \n\n";
			cout << "Student ID: " << tempStudent[i].ID << endl;
			cout << "Student Password: " << tempStudent[i].Password << endl;
			cout << "First Name: " << tempStudent[i].fName << endl;
			cout << "Last Name: " << tempStudent[i].lName << endl;
			cout << "Email Address: " << tempStudent[i].email << endl << endl;

			cout << "Emergency Contact Details: \n\n";
			cout << "First Name: " << tempStudent[i].parent.fName << endl;
			cout << "Last Name: " << tempStudent[i].parent.lName << endl;
			cout << "Contact Number: " << tempStudent[i].parent.contactNumber << endl << endl;

			cout << "Student Grades: \n\n";
			cout << "Class 1: " << tempStudent[i].class1.code << "\tGrade: " << tempStudent[i].class1.studentGrade << "%" << "\tClass Tuition: $" << tempStudent[i].class1.courseCost << endl;
			cout << "Class 2: " << tempStudent[i].class2.code << "\tGrade: " << tempStudent[i].class2.studentGrade << "%" << "\tClass Tuition: $" << tempStudent[i].class2.courseCost << endl;
			cout << "Class 3: " << tempStudent[i].class3.code << "\tGrade: " << tempStudent[i].class3.studentGrade << "%" << "\tClass Tuition: $" << tempStudent[i].class3.courseCost << endl;
			cout << "Class 4: " << tempStudent[i].class4.code << "\tGrade: " << tempStudent[i].class4.studentGrade << "%" << "\tClass Tuition: $" << tempStudent[i].class4.courseCost << endl << endl;
		}
		char returnMain;
		cout << "Press x to return to Admin Main Menu: "; cin >> returnMain;
		if (returnMain == 'x' || returnMain == 'X') {
			adminDatabase(student);
		}
		else {
			cout << "\nInvalid input. Press x to return to main menu";
		}
	}


	void editRoll() {
		system("cls");
		string classSearch;
		"Search for class by class code (4 letters and 3 numbers): "; cin >> classSearch;
		//if classSearch == any of the hardcoded classes, display all ID students in class, prompt options to remove or add student from data base --> upon choice, prompt to enter student ID (if in/not in list, student added/removed
	}
	void gradeStudent(vector<Student>& student) {
		system("cls");
		long int IDsearch;
		cout << "Search for student by ID: "; cin >> IDsearch;
		Student s;
		char searchChoice;
		int flag = 0, i;
		string line;
		string property;
		fstream StudentDatabase("stDB.csv", ios::in);
		vector<Student> tempStudent;
		while (getline(StudentDatabase, line)) {
			istringstream linestream(line);
			getline(linestream, property, ',');
			stringstream ss(property);
			ss >> s.ID;
			getline(linestream, property, ',');
			s.Password = property;
			getline(linestream, property, ',');
			s.fName = property;
			getline(linestream, property, ',');
			s.lName = property;
			getline(linestream, property, ',');
			s.email = property;
			getline(linestream, property, ',');
			s.parent.fName = property;
			getline(linestream, property, ',');
			s.parent.lName = property;
			getline(linestream, property, ',');
			stringstream sc(property);

			getline(linestream, property, ',');
			s.class1.code = property;
			getline(linestream, property, ',');
			stringstream aCG(property);
			aCG >> s.class1.studentGrade;
			getline(linestream, property, ',');
			stringstream aCC(property);
			aCC >> s.class1.courseCost;

			getline(linestream, property, ',');
			s.class2.code = property;
			getline(linestream, property, ',');
			stringstream bCG(property);
			bCG >> s.class2.studentGrade;
			getline(linestream, property, ',');
			stringstream bCC(property);
			bCC >> s.class2.courseCost;

			getline(linestream, property, ',');
			s.class3.code = property;
			getline(linestream, property, ',');
			stringstream cCG(property);
			cCG >> s.class3.studentGrade;
			getline(linestream, property, ',');
			stringstream cCC(property);
			cCC >> s.class3.courseCost;

			getline(linestream, property, ',');
			s.class4.code = property;
			getline(linestream, property, ',');
			stringstream dCG(property);
			dCG >> s.class4.studentGrade;
			getline(linestream, property, ',');
			stringstream dCC(property);
			dCC >> s.class4.courseCost;
			sc >> s.parent.contactNumber;
			tempStudent.push_back(s);
			if (s.ID == IDsearch) {
				flag = 1;
			}
		}
		switch (flag) {
		case 0:
			cout << "No student with ID: " << IDsearch << " was found\n";
			cout << "Search again? Y/N: "; cin >> searchChoice;
			if (searchChoice == 'y' || searchChoice == 'Y') {
				gradeStudent(student);
			}
			else {
				cout << "\n Returning to Admin main menu...";
				Sleep(1000);
				adminDatabase(student);
			}
			break;
		case 1:
			cout << "\nStudent " << IDsearch << " " << s.fName << " " << s.lName << " found\nFinding student grades...\n\n\n";
			Sleep(1000);
			cout << "Student Grades: \n\n";
			cout << "Class 1: " << s.class1.code << "\tGrade: " << s.class1.studentGrade << "%" << endl;
			cout << "Class 2: " << s.class2.code << "\tGrade: " << s.class2.studentGrade << "%" << endl;
			cout << "Class 3: " << s.class3.code << "\tGrade: " << s.class3.studentGrade << "%" << endl;
			cout << "Class 4: " << s.class4.code << "\tGrade: " << s.class4.studentGrade << "%" << endl << endl;
			break;
		}
		int classSelect;
		int gradeChange;
		
		cout << "\n\nWhich class are you adding/changing a grade for?\nPress 1 for: " << s.class1.code << "\nPress 2 for: " << s.class2.code << "\nPress 3 for: " << s.class3.code << "\nPress 4 for: " << s.class4.code << endl;
		cout << "Select class: "; cin >> classSelect;
		switch (classSelect) {
		case 1:
			cout << "Enter new grade for class 1: "; cin >> gradeChange;
			//add code to find s.class1.code on DB and change it to value given as gradeChange
			s.class1.studentGrade = gradeChange; //surely cant be this simple -- its not - doesnt change it at all
			StudentDatabase << s.class1.studentGrade << endl;
			cout << "Grade successfully updated\n\n";
			break;
		case 2:
			cout << "Enter new grade for class 2: "; cin >> gradeChange;
			s.class2.studentGrade = gradeChange;
			StudentDatabase << s.class2.studentGrade << endl;
			cout << "Grade successfully updated\n\n";
			break;
		case 3:
			cout << "Enter new grade for class 3: "; cin >> gradeChange;
			s.class3.studentGrade = gradeChange;
			StudentDatabase << s.class3.studentGrade << endl;
			cout << "Grade successfully updated\n\n";
			break;
		case 4:
			cout << "Enter new grade for class 4: "; cin >> gradeChange;
			s.class4.studentGrade = gradeChange;
			StudentDatabase << s.class4.studentGrade << endl;
			cout << "Grade successfully updated\n\n";
			break;
		default:
			cout << "Invalid Input. Enter 1,2,3 or 4 to select a class\n";
			gradeStudent(student);
		}
		StudentDatabase.close();
		char anotherChar;
		cout << "Update Another Grade? y/n: "; cin >> anotherChar;
		if (anotherChar == 'y' || anotherChar == 'Y') {
			gradeStudent(student);
		}
		else {
			cout << "\n\nDirecting to Admin Menu...";
			Sleep(1000);
			adminDatabase(student);
		}
	}

void studentDatabase() {
	system("cls");
	ShowHeader();
	int menuChoice;
	cout << "***Student Database Access***\n\n";
	cout << "Press 1 to edit person details\n"; //fname lname, email, parent details
	cout << "Press 2 to view enrolled classess\n"; //brings to next menu that shows class 1,2,3,4 (name)
	cout << "Press 3 to grade summary for the year\n"; // brings up grades for class 1,2,3,4
	cout << "Press 4 to see tuition cost summary\n";// opens cost breakdown for each class
	cout << "Press 5 to see all courses available this semester\n";// opens a list of all available courses
	cout << "Press 6 to log out\n";// returns to main menu
	cout << "Enter your choice"; cin >> menuChoice;

	switch (menuChoice) {
	case 1: editStudent();
		break;
	case 2: studentClassSum();
		break;
	case 3: StudentGradeSum();
		break;
	case 4: studentTuitionSum();
		break;
	case 5: studentAvailableCourses();
		break;
	case 6:
		cout << "\n\nLogging out\nReturning to main menu...";
		Sleep(1000);
		main();
	};

}

void editStudent() {
	//press 1 to edit PW
	//2 to edit fname
	//3 to edit lname
	//4 to edit email
	//5 parent fname
	//6 parent lname
	//7 parent contact no.
	//8 to exit

	//link to functions
}
void studentClassSum() {
	//print details for all enrolled classes
}
void StudentGradeSum() {
	//print grades for all enrolled classes along with a total grade average that converted to a grade letter scale system (50-60 = c, 60-70 = b, 70-80 ect)
}
void studentTuitionSum() {
	// print out cost of each class and the total tuition cost for the year.
}


void studentAvailableCourses() // this is case 5 in the main student area
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	ShowHeader();
	

	ifstream inputFile;
	inputFile.open("courses.csv"); //courseID, coursename, semester, YEAR, costlocal, costinternational
	string line = "";

	vector<CourseRecord> Courses;
	while (getline(inputFile, line)) {

		stringstream inputString(line);

		//courseID, coursename, semester, YEAR, costlocal, costinternational, teacher per file
		string id;
		string courseName;
		string semester;
		int yEAR;
		double costLocal;
		double costInternational;
		string teacher;
		string tempString;

		getline(inputString, id, ',');
		getline(inputString, courseName, ',');
		getline(inputString, semester, ',');
		getline(inputString, tempString, ',');
		yEAR = atoi(tempString.c_str());
		getline(inputString, tempString, ',');
		costLocal = atof(tempString.c_str());
		getline(inputString, tempString, ',');
		costInternational = atof(tempString.c_str());
		getline(inputString, teacher, ',');


		CourseRecord course(id, courseName, semester, yEAR, costLocal, costInternational, teacher);
		Courses.push_back(course);
		line = "";
	}

	displayCourses(Courses);
	inputFile.close();


	SetConsoleTextAttribute(color, 7);
	
	Sleep(1000);
	endMenuchoise();


}

void endMenuchoise() // this is for the student
{
	int menuChoiceStudent;
	cout << "*** Student Database Access*** \n\n";
	cout << "Press 1 to return to the student database\n"; // returns to student database
	cout << "Press 2 to return to the main menu\n"; // returns to main menu
	cout << "Press 3 or anything else to EXIT the program\n";// EXIT
	cout << "Enter your choice"; cin >> menuChoiceStudent;

	switch (menuChoiceStudent) {
	case 1:
		cout << "\n\nLogging out\nReturning to main menu...";
		Sleep(1000);
		studentDatabase();
	case 2:
		cout << "\n\nLogging out\nReturning to main menu...";
		Sleep(1000);
		main();
	case 3:
		cout << "\n\nClosing App...";
		Sleep(500);
		exit(1);
	default:
		cout << "\n\nClosing App.. As not 1, 2 or 3 - you have been logged out.";
		Sleep(500);
		exit(1);
	};

}

void ShowHeader() //the function which shows the header on each screen
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	struct tm newtime;
	__time32_t aclock;
	char buffer[32];
	errno_t errNum;
	_time32(&aclock);
	_localtime32_s(&newtime, &aclock);
	errNum = asctime_s(buffer, 32, &newtime);

	SetConsoleTextAttribute(color, 10);
	cout << endl << "---------------------------------------------------------------------------------------------\n";
	SetConsoleTextAttribute(color, 15);
	cout << "                          Welcome to Victoria University \n";
	SetConsoleTextAttribute(color, 2);
	printf("                  Current date and time: %s", buffer);
	SetConsoleTextAttribute(color, 10);
	cout << "---------------------------------------------------------------------------------------------\n";
	cout << endl << endl;
	SetConsoleTextAttribute(color, 15);
	return;
}
