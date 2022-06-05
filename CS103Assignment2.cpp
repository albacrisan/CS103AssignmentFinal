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
using namespace std;

struct Parent {
	string fName;
	string LName;
	long int contactNumber;
};
struct Teacher {
	string fName;
	string lName;

};
struct classStr {
	string code;
	float studentGrade;
	float courseCost;
	Teacher teacher;
};

struct Student {
	long int ID;
	string PW;
	string fName;
	string lName;
	Parent parent;
	classStr class1;
	classStr class2;
	classStr class3;
	classStr class4;

	Student() {
		ID = 0;
		PW = "PW";
		fName = "FirstName";
		lName = "LastName";

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
	cout << "Create your password. Password must container uppercase,lowercase & number: "; cin >> s.PW;
	cout << "Enter your first name: "; cin >> s.fName;
	cout << "Enter your last name: "; cin >> s.lName;

	student.push_back(s);
	fstream StudentDatabase("stDB.csv", ios::app);
	StudentDatabase << s.ID << "," << s.PW << endl;
	StudentDatabase.close();
	cout << "\n\nRegistration Successfull\nDirecting to main menu...";
	Sleep(1000);
	system("cls");
	main();
	return(student);

}
vector <Student> StudentLogin(vector<Student>& student) {
	system("cls");
	ShowHeader();
	Student s;
	string attemptPW;
	long int attemptID;
	int counter = 3, flag = 0;
	while (counter != 0) {
		cout << "***Student Login***\n\n";
		cout << "Enter ID: "; cin >> attemptID;
		cout << "Enter PW: "; cin >> attemptPW;

		fstream StudentDatabase("stDB.csv", ios::in);
		while (StudentDatabase >> s.ID >> s.PW) {
			if (attemptID == s.ID && attemptPW == s.PW) {// not inputting the right variable for it to read off the spreadsheet
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
	}
	cout << "Closing app...\n\n\n\n";
	Sleep(1000);
	exit(1);
	return(student);
}

void adminLogin() {
	system("cls");
	int counter = 3;
	long int adminID = 000000, enteredID;
	string adminPW = "Password", enteredPW;
	while (counter != 0) {
		cout << "***Admin Login***\n";
		cout << "Enter Admin ID: "; cin >> enteredID;
		cout << "Enter Admin PW: "; cin >> enteredPW;
		if (adminID == enteredID) {
			cout << "\n\nLogin Successful\nWelcome admin. Opening Database now...";
			Sleep(1000);
			adminDatabase();
			break;


		}
		else {
			counter--;
			cout << "\nInvalid ID or PW " << counter << " attempts remaining\n";
		}
	}
	cout << "0 login attempts remaining\n Closing app...";
	exit(3);
}

void adminDatabase() {
	system("cls");
	ShowHeader();
	cout << "***Admin Database Access***\n\n";
}
void studentDatabase() {
	system("cls");
	ShowHeader();
	cout << "***Student Database Access***\n\n";
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

