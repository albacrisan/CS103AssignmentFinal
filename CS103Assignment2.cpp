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
	classStr(string c = "ClassCode", float sG = 0.5, float cC = 7000) {
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

vector <Student> Registration(vector<Student>& student);
vector <Student> StudentLogin();
void adminLogin();
void adminDatabase();
void studentDatabase();

//admin Database menu option functions
void studentSearch();
void printDatabase();
void editRoll();
void gradeStudent();

void editStudent();
void studentClassSum();
void StudentGradeSum();
void studentTuitionSum();

void ShowHeader();

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
			adminLogin();
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
	cout << "***Student Registration***\n\n";
	cout << "Please Enter your Student ID (6 digit Number): "; cin >> s.ID;
	cout << "Create your password. Password must container uppercase,lowercase & number: "; cin >> s.Password;
	cout << "Enter your first name: "; cin >> s.fName;
	cout << "Enter your last name: "; cin >> s.lName;
	student.push_back(s);
	fstream StudentDatabase("stDB.csv", ios::app);
	for (int i = 0; i < student.size(); i++) {
		StudentDatabase << s.ID << "," << s.Password << "," << s.fName <<"," << s.lName << endl;
	}
	StudentDatabase.close();
	cout << "\n\nRegistration Successfull\nDirecting to main menu...";
	Sleep(1000);
	system("cls");
	main();
	return(student);

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
			cout << "\nLogin successfull. Welcome " << s.fName << " " << s.lName <<"\nDirecting you to your student database...\n";
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

void adminLogin() {
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
			adminDatabase();
			break;
		}
	}
	cout << "Closing app...\n\n\n\n";
	Sleep(1000);
	exit(3);
}

void adminDatabase() {
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
	case 1: studentSearch();
		break;
	case 2: printDatabase();
		break;
	case 3: editRoll();
		break;
	case 4: gradeStudent();
		break;
	case 5:
		cout << "\n\nLogging out\nReturning to main menu...";
		Sleep(1000);
		main();
	};
}
	void studentSearch() {
		system("cls");
		long int IDsearch;
		cout << "Search for student by ID: "; cin >> IDsearch;
		//if IDsearch == any ID on database, Cout all the student data line by line with formating.
	}
	void printDatabase() {
		//prints database with formating
	}
	void editRoll() {
		system("cls");
		string classSearch;
		"Search for class by class code (4 letters and 3 numbers): "; cin >> classSearch;
		//if classSearch == any of the hardcoded classes, display all ID students in class, prompt options to remove or add student from data base --> upon choice, prompt to enter student ID (if in/not in list, student added/removed
	}
	void gradeStudent() {
		system("cls");
		long int IDsearch;
		cout << "Search for student by ID: "; cin >> IDsearch;
		//if IDsearch == ID on database, bring up student name. give option to select which class to add grade to (pull from classes on database that are assigned to the student)
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
	cout << "Press 5 to log out\n";// returns to main menu
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
	case 5:
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
