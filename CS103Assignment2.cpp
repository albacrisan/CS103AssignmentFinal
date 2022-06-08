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
#include<ctime> 
#include <map>
#include<cstdlib> //for exit() and system(“cls”) functions
#include<cstring> //for all string functions
#include<conio.h> //for getch() function
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
vector <Student> StudentLogin(vector<Student>& student);
void adminLogin();
void adminDatabase();

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
			StudentLogin(student);
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
		Registration(student);
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
	StudentDatabase << s.ID << "," << s.Password << endl;
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
	vector<Student> tempStudent;
	string attemptPW;
	long int attemptID;
	int counter = 3, flag = 0;
	while (counter != 0) {
		cout << "***Student Login***\n\n";
		cout << "Enter ID: "; cin >> attemptID;
		cout << "Enter PW: "; cin >> attemptPW;
		string line;
		string property;
		fstream StudentDatabase("stDB.csv", ios::in);
		while (getline(StudentDatabase, line, ',')) {
			cout << line << endl;
			istringstream linestream(line);
			getline(linestream, property, ',');
			s.Password = property;
			getline(linestream, property, ',');
			stringstream ss(property);
			ss >> s.ID;

			if (attemptID == s.ID && attemptPW == s.Password) {// not inputting the right variable for it to read off the spreadsheet
				flag = 1;
			}
		}
		switch (flag) {
		case 0:
			counter--;
			cout << "\nIncorrect ID or Password\n" << counter << " login attempts remaining\n";
			break;

		case 1:
			cout << "\nLogin successfull\nDirecting you to database...\n";
			Sleep(1000);
			break;
		}
		tempStudent.push_back(s);
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
	cout << "Press 4 to edit class information\n"; // add or remove class, edit class name, tuition cost
	cout << "Press 5 to assign student grades\n"; // add or change student grade for each class
	cout << "Press 6 to log out\n"; // return to main and log out
	cout << "Enter your choice: "; cin >> menuChoice;

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
	cout << "Press 5 to log out\n"; cin >> menuChoice;// returns to main menu
	cout << "Enter your choice\n"; cin >> menuChoice;
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

