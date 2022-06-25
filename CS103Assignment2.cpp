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
	string ID;
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
vector <Student> StudentLogin(vector<Student>& tempStudent);
void adminLogin(vector<Student>& tempStudent);
void adminDatabase(vector<Student>& tempStudent);
void studentDatabase(vector<Student>& tempStudent);
vector <Student> readFromFile();

//admin Database menu option functions
void studentSearch(vector<Student>& tempStudent);
void printDatabase(vector<Student>& tempStudent);
void classGradeAverages(vector<Student>& tempStudent);
void tuitionTotal(vector<Student>& tempStudent);

//Student functions
void editStudent(vector<Student>& tempStudent);
void editoptions(vector<Student>& tempStudent);
vector <Student> editPersonalContactDetails(vector<Student>& tempStudent);
vector <Student> editEmergencyContactDetails(vector<Student>& tempStudent);
void studentClassSum(vector<Student>& tempStudent);
void StudentGradeSum(vector<Student>& tempStudent);
void studentTuitionSum(vector<Student>& tempStudent);
void studentAvailableCourses(vector<Student>& tempStudent);

//Headers and functionality
void ShowHeader();
void endMenuchoise(vector<Student>& tempStudent);

int main() {

	ShowHeader();


	vector <Student> tempStudent;
	tempStudent = readFromFile();
	int menuChoice, loginChoice;
	//cout << "***University Database***\n\n\n";
	cout << " Press 1 to Login\n Press 2 to Register\n Press 3 to exit Program\n Enter your choice: "; cin >> menuChoice;
	switch (menuChoice) {
	case 1:
		cout << "\n\n Press 1 for Student login\n Press 2 for Admin login\n Enter your choice: "; cin >> loginChoice;
		if (loginChoice == 1) {
			cout << "\n\n Directing to Student Login...";
			Sleep(500);
			StudentLogin(tempStudent);
			break;
		}
		else if (loginChoice == 2) {
			cout << "\n\n Directing to Admin Login...";
			Sleep(500);
			adminLogin(tempStudent);
			break;
		}
		else {
			cout << " Invalid input. Press 1 or 2";
			Sleep(1000);
			system("cls");
			main();
			break;
		}
	case 2:
		cout << "\n\n Directing to Student Registration...";
		Sleep(500);
		Registration(tempStudent);
		break;
	case 3:
		cout << "\n\n Closing App...";
		Sleep(500);
		exit(1);
	default:
		cout << "\n\n Invalid Input. Press 1, 2 or 3";
		Sleep(1000);
		system("cls");
		main();
	}


}

vector <Student> Registration(vector<Student>& tempStudent) {
	system("cls");
	ShowHeader();
	Student s;

	cout << "           ***Student Registration***\n\n";
	cout << " Please Enter your Student ID (6 digit Number): ";
	cin >> s.ID;
	if (s.ID.size() == 6) {
		int IDNumFlag = 0, idIndex;
		for (idIndex = 0; idIndex < s.ID.size(); idIndex++) {
			if (isdigit(s.ID[idIndex])) {
				IDNumFlag = 1;

			}
		}
		if (IDNumFlag == 0) {
			cout << " ID must only contain digits\n\n\n"; //runs this code block straight away and regardless of user input
			Sleep(1500);
			Registration(tempStudent);
		}
	}
	cout << " Create your password. Password must container uppercase,lowercase & number and 8+ character: ";
	cin >> s.Password;
	if (s.Password.size() > 7) {
		int PWflaglength = 0, PWflaglow = 0, PWflagHigh = 0, PWflagNum = 0, passwordIndex;
		for (passwordIndex = 0; passwordIndex < s.Password.size(); passwordIndex++) {
			if (isdigit(s.Password[passwordIndex])) {
				PWflagNum = 1;
			}
		}
		if (PWflagNum == 0) {
			cout << " Password must contain at least 1 number\n";
			Sleep(1500);
			Registration(tempStudent);
		}
		for (passwordIndex = 0; passwordIndex < s.Password.size(); passwordIndex++) {
			if (islower(s.Password[passwordIndex])) { // not recognising lower case letter. -- only looking at the first letter
				PWflaglow = 1;
			}
		}
		if (PWflaglow == 0) {
			cout << " Password must contain at least 1 lowercase letter\n";
			Sleep(1500);
			Registration(tempStudent);
		}
		for (passwordIndex = 0; passwordIndex < s.Password.size(); passwordIndex++) {
			if (isupper(s.Password[passwordIndex])) {
				PWflagHigh = 1;
			}
		}
		if (PWflagHigh == 0) {
			cout << " Password must contain atleast 1 uppercase letter\n";
			Sleep(1500);
			Registration(tempStudent);
		}
		for (passwordIndex = 0; passwordIndex < s.Password.size(); passwordIndex++) {
			if (s.Password.size() > 7) {
				PWflaglength = 1;
			}
		}
		if (PWflaglength == 0) {
			cout << " Password must at least 8 digits long\nTry again";
			Sleep(1500);
			Registration(tempStudent);

		}
	}
	cout << " \n\n *Personal Contact Details*:\n\n";
	cout << " Enter your first name: "; cin >> s.fName;
	cout << " Enter your last name: "; cin >> s.lName;
	cout << " Enter you email address: "; cin >> s.email;
	cout << endl << endl;
	cout << " *Emergency Contact Details*:\n\n";
	cout << " Enter first name: "; cin >> s.parent.fName;
	cout << " Enter last name: "; cin >> s.parent.lName;
	cout << " Enter contact number: "; cin >> s.parent.contactNumber;
	tempStudent.push_back(s);
	fstream StudentDatabase("stDB.csv", ios::app);
	StudentDatabase << s.ID << "," << s.Password << "," << s.fName << "," << s.lName << "," << s.email << "," << s.parent.fName << "," << s.parent.lName << "," << s.parent.contactNumber << "," << s.class1.code << "," << s.class1.studentGrade << "," << s.class1.courseCost << "," << s.class2.code << "," << s.class2.studentGrade << "," << s.class2.courseCost << "," << s.class3.code << "," << s.class3.studentGrade << "," << s.class3.courseCost << "," << s.class4.code << "," << s.class4.studentGrade << "," << s.class4.courseCost << endl;
	StudentDatabase.close();
	cout << "\n\n Registration Successfull\n Directing to main menu...";
	Sleep(1000);
	system("cls");
	main();
	return(tempStudent);


}
vector <Student> readFromFile() {
	fstream StudentDatabase("stDB.csv", ios::in);
	vector<Student> tempStudent;
	Student s;
	string line;
	string property;

	while (getline(StudentDatabase, line)) {
		istringstream linestream(line);
		getline(linestream, property, ',');
		s.ID = property;
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
	StudentDatabase.close();
	return(tempStudent);

}
vector <Student> StudentLogin(vector<Student>& tempStudent) {
	system("cls");
	ShowHeader();
	Student s;
	string attemptPW;
	string attemptID;
	int counter = 3, flag = 0;
	cout << "           ***Student Login***\n\n";
	while (counter != 0) {
		
		cout << " Enter ID: "; cin >> attemptID;
		cout << " Enter PW: "; cin >> attemptPW;
		string line;
		string property;
		fstream StudentDatabase("stDB.csv", ios::in);
		while (getline(StudentDatabase, line)) {
			istringstream linestream(line);
			getline(linestream, property, ',');
			s.ID = property;
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
			cout << "\n Incorrect ID or Password\n " << counter << " login attempts remaining\n\n";
			break;

		case 1:
			cout << "\n Login successfull. Welcome\n Directing you to your student database...\n";
			Sleep(1000);
			studentDatabase(tempStudent);
			break;
		}
		StudentDatabase.close();
	}
	cout << " Closing app...\n\n\n\n";
	Sleep(1000);
	exit(1);
	return(tempStudent); // is this loading into the right vector to call later??
}

void adminLogin(vector<Student>& tempStudent) {
	system("cls");
	int counter = 3, flag = 0;
	long int adminID = 000000, enteredID;
	string adminPW = "Password", enteredPW;
	cout << "           ***Admin Login***\n\n";
	while (counter != 0) {
		
		cout << " Enter Admin ID: "; cin >> enteredID;
		cout << " Enter Admin PW: "; cin >> enteredPW;
		if (adminID == enteredID && adminPW == enteredPW) {
			flag = 1;
		}
		switch (flag) {
		case 0:
			counter--;
			cout << "\n Incorrect ID or Password\n " << counter << " login attempts remaining\n\n";
			break;

		case 1:
			cout << "\n Login successfull\n Directing you to database...\n";
			Sleep(1000);
			adminDatabase(tempStudent);
			break;
		}
	}
	cout << "\n\n Closing app...\n\n\n\n";
	Sleep(1000);
	exit(3);
}

void adminDatabase(vector<Student>& tempStudent) {
	system("cls");
	ShowHeader();
	int menuChoice;
	cout << "           ***Admin Database Home***\n\n";
	cout << " Press 1 to search for a student by ID number\n"; // search for student by ID which spits out student data in full if matching ID is found
	cout << " Press 2 to view student full student database\n";// prints all data in the student database
	cout << " Press 3 to class grade averages\n"; 
	cout << " Press 4 to view enrollment tuition total\n"; 
	cout << " Press 5 to log out\n"; // return to main and log out
	cout << " Enter your choice: "; cin >> menuChoice;

	switch (menuChoice) {
	case 1: studentSearch(tempStudent);
		break;
	case 2: printDatabase(tempStudent);
		break;
	case 3: classGradeAverages(tempStudent);
		break;
	case 4: tuitionTotal(tempStudent);
		break;
	case 5:
		cout << "\n\n Logging out\n Returning to main menu...";
		Sleep(1000);
		main();
	};
}



void studentSearch(vector<Student>& tempStudent) {
	system("cls");
	ShowHeader();
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	string IDsearch;
	SetConsoleTextAttribute(color, 11);
	cout << "           ***Student Search & Display***\n\n\n\n";
	SetConsoleTextAttribute(color, 11);
	cout << " Search for student by ID: "; cin >> IDsearch;
	Student s;
	char searchChoice = 'n';
	int flag = 0;
	string line;
	string property;
	int i;
	
	for (i = 0; i < tempStudent.size(); i++) {
		if (tempStudent[i].ID == IDsearch) {
			SetConsoleTextAttribute(color, 2);
			cout << "\n Student " << IDsearch << " found\n Loading student data...\n\n\n";
			Sleep(1000);
			SetConsoleTextAttribute(color, 11);
			cout << " *Personal Contact Details*\n\n";
			cout << " Student ID:       " << tempStudent[i].ID << endl;
			cout << " Student Password: " << tempStudent[i].Password << endl;
			cout << " First Name:       " << tempStudent[i].fName << endl;
			cout << " Last Name:        " << tempStudent[i].lName << endl;
			cout << " Email Address:    " << tempStudent[i].email << endl << endl;

			cout << " *Emergency Contact Details*\n\n";
			cout << " First Name:       " << tempStudent[i].parent.fName << endl;
			cout << " Last Name:        " << tempStudent[i].parent.lName << endl;
			cout << " Contact Number:   " << tempStudent[i].parent.contactNumber << endl << endl;

			cout << " *Student Grades*\n\n";
			cout << " Class 1: " << tempStudent[i].class1.code << "\tGrade: " << tempStudent[i].class1.studentGrade << "%\tClass Tuition: " << tempStudent[i].class1.courseCost << endl;
			cout << " Class 2: " << tempStudent[i].class2.code << "\tGrade: " << tempStudent[i].class2.studentGrade << "%\tClass Tuition: " << tempStudent[i].class2.courseCost << endl;
			cout << " Class 3: " << tempStudent[i].class3.code << "\tGrade: " << tempStudent[i].class3.studentGrade << "%\tClass Tuition: " << tempStudent[i].class3.courseCost << endl;
			cout << " Class 4: " << tempStudent[i].class4.code << "\tGrade: " << tempStudent[i].class4.studentGrade << "%\tClass Tuition: " << tempStudent[i].class4.courseCost << endl << endl;

			cout << " Search Again? Y/N: "; cin >> searchChoice;
			if (searchChoice == 'y' || searchChoice == 'Y') {
				studentSearch(tempStudent);
			}
			else {
				cout << "\n Returning to Admin main menu...";
				Sleep(1000);
				adminDatabase(tempStudent);
			}
		}
	}
	SetConsoleTextAttribute(color, 4);
	cout << " No student with ID: " << IDsearch << " was found\n";
	SetConsoleTextAttribute(color, 11);
	cout << " Search again? Y/N: "; cin >> searchChoice;
	if (searchChoice == 'y' || searchChoice == 'Y') {
			studentSearch(tempStudent);
	}
	else {
		cout << "\n Returning to Admin main menu...";
		Sleep(1000);
		adminDatabase(tempStudent);
	}
}

void printDatabase(vector<Student>& tempStudent) {
	system("cls");
	ShowHeader();
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "           ***Full Student Database***";
	cout << " Printing full database...\n\n\n\n";
	Sleep(1000);
	string line;
	Student s;
	string property;
	
	for (int i = 0; i < tempStudent.size(); i++) {
		cout << " Student " << tempStudent[i].ID << ":\n\n";

		cout << " Personal Contact Details: \n\n";
		cout << " Student ID:       " << tempStudent[i].ID << endl;
		cout << " Student Password: " << tempStudent[i].Password << endl;
		cout << " First Name:       " << tempStudent[i].fName << endl;
		cout << " Last Name:        " << tempStudent[i].lName << endl;
		cout << " Email Address:    " << tempStudent[i].email << endl << endl;

		cout << " Emergency Contact Details: \n\n";
		cout << " First Name:       " << tempStudent[i].parent.fName << endl;
		cout << " Last Name:        " << tempStudent[i].parent.lName << endl;
		cout << " Contact Number:   " << tempStudent[i].parent.contactNumber << endl << endl;

		cout << " Student Grades: \n\n";
		cout << " Class 1: " << tempStudent[i].class1.code << "\tGrade: " << tempStudent[i].class1.studentGrade << "%" << "\tClass Tuition: $" << tempStudent[i].class1.courseCost << endl;
		cout << " Class 2: " << tempStudent[i].class2.code << "\tGrade: " << tempStudent[i].class2.studentGrade << "%" << "\tClass Tuition: $" << tempStudent[i].class2.courseCost << endl;
		cout << " Class 3: " << tempStudent[i].class3.code << "\tGrade: " << tempStudent[i].class3.studentGrade << "%" << "\tClass Tuition: $" << tempStudent[i].class3.courseCost << endl;
		cout << " Class 4: " << tempStudent[i].class4.code << "\tGrade: " << tempStudent[i].class4.studentGrade << "%" << "\tClass Tuition: $" << tempStudent[i].class4.courseCost << endl << endl;
	}
	char returnMain = 'y';
	cout << " Press x to return to Admin menu: ";
	while (returnMain != 'x' && returnMain != 'X') {
		cin >> returnMain;
		if (returnMain == 'x' || returnMain == 'X') {
			adminDatabase(tempStudent);
		}
		else {
			cout << "\n Invalid Input. Press x to return to main menu: ";
		}
	}
}

void classGradeAverages(vector<Student>& tempStudent) {
	system("cls");
	ShowHeader();
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "           ***Class Grade Averages***\n\n\n";
	Student s;
	char searchChoice;
	int i;
	tempStudent = readFromFile();
	float ACCY302c = 0, ACCY303c = 0, ACCY317c = 0, ACCY321c = 0, ACCY302a = 0, ACCY303a = 0, ACCY317a = 0, ACCY321a = 0, average = 0;
	if (tempStudent.size() == 0) {
		char returnMain = 'y';
		cout << " Empty Database\n\n\n\n";
		cout << " Press x to return to Admin menu: ";
		while (returnMain != 'x' && returnMain != 'X') {
			cin >> returnMain;
			if (returnMain == 'x' || returnMain == 'X') {
				adminDatabase(tempStudent);
			}
			else {
				cout << "\n Invalid Input. Press x to return to main menu: ";
			}
		}
	}
	for (i = 0; i < tempStudent.size(); i++) {
		ACCY302c += tempStudent[i].class1.studentGrade;
		ACCY303c += tempStudent[i].class2.studentGrade;
		ACCY317c += tempStudent[i].class3.studentGrade;
		ACCY321c += tempStudent[i].class4.studentGrade;
		
	}
	ACCY302a = ACCY302c/tempStudent.size();
	ACCY303a = ACCY303c/tempStudent.size();
	ACCY317a = ACCY317c/tempStudent.size();
	ACCY321a = ACCY321c/tempStudent.size();
	average = (ACCY302a + ACCY303a + ACCY317a + ACCY321a) / 4;

	cout << " ACCY302 student grade average: " << fixed << setprecision(2) << ACCY302a << "%\n";
	cout << " ACCY303 student grade average: " << fixed << setprecision(2) << ACCY303a << "%\n";
	cout << " ACCY317 student grade average: " << fixed << setprecision(2) << ACCY317a << "%\n";
	cout << " ACCY321 student grade average: " << fixed << setprecision(2) << ACCY321a << "%\n";

	cout << "\n Average grade across classes:  " << fixed << setprecision(2) << average << "%\n\n";

	char returnMain = 'y';
	cout << " Press x to return to Admin menu: ";
	while (returnMain != 'x' && returnMain != 'X') {
		cin >> returnMain;
		if (returnMain == 'x' || returnMain == 'X') {
			adminDatabase(tempStudent);
		}
		else {
			cout << "\n Invalid Input. Press x to return to main menu: ";
		}
	}

}

void tuitionTotal(vector<Student>& tempStudent) {
	system("cls");
	ShowHeader();
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "           ***Tuition total***\n\n\n";
	Student s;
	int i;
	float tuitionTotal = 0, tuitionAverage;
	if (tempStudent.size() == 0) {
		char returnMain = 'y';
		cout << " Empty Database\n\n";
		cout << " Press x to return to Admin menu: ";
		while (returnMain != 'x' && returnMain != 'X') {
			cin >> returnMain;
			if (returnMain == 'x' || returnMain == 'X') {
				adminDatabase(tempStudent);
			}
			else {
				cout << "\n Invalid Input. Press x to return to main menu: ";
			}
		}
	}
	for (i = 0; i < tempStudent.size(); i++) {
		tuitionTotal += (tempStudent[i].class1.courseCost + tempStudent[i].class2.courseCost + tempStudent[i].class3.courseCost + tempStudent[i].class4.courseCost);
	}
	tuitionAverage = tuitionTotal / tempStudent.size();
	cout << " " << tempStudent.size() << " students enrolled" << endl;
	cout << " Total income from student enrollments: $" << tuitionTotal << endl;
	cout << " Average tuition per enrolled student:  $" << tuitionAverage << endl << endl << endl;

	char returnMain = 'y';
	cout << " Press x to return to Admin menu: ";
	while (returnMain != 'x' && returnMain != 'X') {
		cin >> returnMain;
		if (returnMain == 'x' || returnMain == 'X') {
			adminDatabase(tempStudent);
		}
		else {
			cout << "\n Invalid Input. Press x to return to main menu: ";
		}
	}
}

void studentDatabase(vector<Student>& tempStudent) {
	system("cls");
	ShowHeader();
	int menuChoice;
	cout << "           ***Student Database Access***\n\n";
	cout << " Press 1 to view your details\n"; //fname lname, email, parent details
	cout << " Press 2 to edit your details\n"; //brings to next menu that shows class 1,2,3,4 (name)
	cout << " Press 3 to grade summary for the year\n"; // brings up grades for class 1,2,3,4
	cout << " Press 4 to see tuition cost summary\n";// opens cost breakdown for each class
	cout << " Press 5 to see all courses available next semester\n";// opens a list of all available courses
	cout << " Press 6 to log out\n";// returns to main menu
	cout << " Enter your choice"; cin >> menuChoice;

	switch (menuChoice) {
	case 1: studentClassSum(tempStudent);
		break;
	case 2: editStudent(tempStudent);
		break;
	case 3: StudentGradeSum(tempStudent);
		break;
	case 4: studentTuitionSum(tempStudent);
		break;
	case 5: studentAvailableCourses(tempStudent);
		break;
	case 6:
		cout << "\n\nLogging out\nReturning to main menu...";
		Sleep(1000);
		main();
	};

}

void editStudent(vector<Student>& tempStudent) {


	//I explain current info (with password but this field can be removed if needed)
	system("cls");
	ShowHeader();
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	string IDsearch;
	SetConsoleTextAttribute(color, 12);
	cout << "Please re-confirm your student ID: "; cin >> IDsearch;
	SetConsoleTextAttribute(color, 7);
	Student s;
	char searchChoice = 'n';
	int flag = 0;
	string line;
	string property;
	tempStudent = readFromFile();
	int i;
	for (i = 0; i < tempStudent.size(); i++) {
		if (tempStudent[i].ID == IDsearch) {
			cout << "\nStudent " << IDsearch << "Success! ID found.\nThis is your current information.\n\n\n";
			Sleep(1000);
			SetConsoleTextAttribute(color, 10);
			cout << "Personal Contact Details\n\n";
			SetConsoleTextAttribute(color, 7);
			cout << "Student ID: " << tempStudent[i].ID << endl;
			cout << "Student Password: " << tempStudent[i].Password << endl;
			cout << "First Name: " << tempStudent[i].fName << endl;
			cout << "Last Name: " << tempStudent[i].lName << endl;
			cout << "Email Address: " << tempStudent[i].email << endl << endl;

			SetConsoleTextAttribute(color, 10);
			cout << "Emergency Contact Details\n\n";
			SetConsoleTextAttribute(color, 7);
			cout << "First Name: " << tempStudent[i].parent.fName << endl;
			cout << "Last Name: " << tempStudent[i].parent.lName << endl;
			cout << "Contact Number: " << tempStudent[i].parent.contactNumber << endl << endl;

			SetConsoleTextAttribute(color, 10);
			cout << "Student Grades and courses\n\n";
			SetConsoleTextAttribute(color, 7);
			cout << "Class 1: " << tempStudent[i].class1.code << "\tGrade: " << tempStudent[i].class1.studentGrade << "%" << endl;
			cout << "Class 2: " << tempStudent[i].class2.code << "\tGrade: " << tempStudent[i].class2.studentGrade << "%" << endl;
			cout << "Class 3: " << tempStudent[i].class3.code << "\tGrade: " << tempStudent[i].class3.studentGrade << "%" << endl;
			cout << "Class 4: " << tempStudent[i].class4.code << "\tGrade: " << tempStudent[i].class4.studentGrade << "%" << endl << endl;

			cout << "Would you like to edit your contact details information? Y/N: "; cin >> searchChoice;
			if (searchChoice == 'y' || searchChoice == 'Y') {
				editoptions(tempStudent);
			}
			else {
				cout << "\n Returning to Student database main menu...";
				Sleep(1000);
				studentDatabase(tempStudent);
			}
		}

	}

}






void editoptions(vector<Student>& tempStudent) {

	system("cls");
	ShowHeader();
	int menuChoice;
	cout << "***Student Database Editing options***\n\n";
	cout << "Press 1 to edit your Personal Contact Details\n"; //fname lname, email, parent details
	cout << "Press 2 to edit your Emergency Contact details\n"; //brings to next menu that shows class 1,2,3,4 (name)
	cout << "Press 3 to log out to the student datatase\n";// returns to student database menu
	cout << "Press 4 to log out to the main datatase\n";// returns to student database menu
	cout << "Press 5 to exit\n";// returns to student database menu
	cout << "Enter your choice"; cin >> menuChoice;

	switch (menuChoice) {
	case 1: editPersonalContactDetails(tempStudent);
		break;
	case 2: editEmergencyContactDetails(tempStudent);
		break;
	case 3:
		cout << "\n\nLogging out\nReturning to main menu...";
		Sleep(1000);
		studentDatabase(tempStudent);
	case 4:
		cout << "\n\nLogging out\nReturning to main menu...";
		Sleep(1000);
		main();
	case 5:
		cout << "\n\nClosing App...";
		Sleep(500);
		exit(1);
	default:
		cout << "\n\nClosing App.. As not 1, 2, 3, 4 or 5 - you have been logged out.";
		Sleep(500);
		exit(1);
	};
}


vector <Student> editPersonalContactDetails(vector<Student>& tempStudent) {



	system("cls");
	ShowHeader();
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	string IDsearch;
	string recPassword;
	SetConsoleTextAttribute(color, 14);
	cout << "                         Edit Personal Contact Details Screen \n\n";
	SetConsoleTextAttribute(color, 7);
	cout << "Please re-confirm your student ID: "; cin >> IDsearch;
	cout << "Please re-confirm your password: "; cin >> recPassword;

	return(tempStudent);
}

vector <Student> editEmergencyContactDetails(vector<Student>& tempStudent) {

	system("cls");
	ShowHeader();
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	string IDsearch;
	string recPassword;
	SetConsoleTextAttribute(color, 14);
	cout << "                         Edit Emergency Contact Details Screen \n\n";
	SetConsoleTextAttribute(color, 7);
	cout << "Please re-confirm your student ID: "; cin >> IDsearch;
	cout << "Please re-confirm your password: "; cin >> recPassword;


	return(tempStudent);
}








void studentClassSum(vector<Student>& tempStudent) {
	//print all current details
	system("cls");
	ShowHeader();
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	string IDsearch;
	string recPassword;
	SetConsoleTextAttribute(color, 14);
	cout << "                         Student Details enquiry screen \n\n";
	SetConsoleTextAttribute(color, 7);
	cout << "Please re-confirm your student ID: "; cin >> IDsearch;
	cout << "Please re-confirm your password: "; cin >> recPassword;
	SetConsoleTextAttribute(color, 7);
	Student s;
	char searchChoice = 'n';
	int flag = 0;
	string line;
	string property;
	tempStudent = readFromFile();

	int i;
	for (i = 0; i < tempStudent.size(); i++) {
		if (tempStudent[i].ID != IDsearch) {
			cout << "\n\nNo student was found. Please verify your student ID.\n\n";    //check ID exists
			break;

		}
		else if (tempStudent[i].ID == IDsearch && tempStudent[i].Password == recPassword) {
			SetConsoleTextAttribute(color, 10);
			cout << "\nWelcome " << tempStudent[i].fName << " " << tempStudent[i].lName << endl;
			SetConsoleTextAttribute(color, 7);
			cout << "Thank you! Your ID " << tempStudent[i].ID << " and its associated password are now confirmed.\n";

			SetConsoleTextAttribute(color, 10);
			cout << "\nPersonal Contact Details on file\n\n";
			SetConsoleTextAttribute(color, 7);
			cout << "Student ID: " << tempStudent[i].ID << endl;
			cout << "Student Password: " << tempStudent[i].Password << endl;
			cout << "First Name: " << tempStudent[i].fName << endl;
			cout << "Last Name: " << tempStudent[i].lName << endl;
			cout << "Email Address: " << tempStudent[i].email << endl << endl;

			SetConsoleTextAttribute(color, 10);
			cout << "Emergency Contact Details\n\n";
			SetConsoleTextAttribute(color, 7);
			cout << "First Name: " << tempStudent[i].parent.fName << endl;
			cout << "Last Name: " << tempStudent[i].parent.lName << endl;
			cout << "Contact Number: " << tempStudent[i].parent.contactNumber << endl << endl;

			SetConsoleTextAttribute(color, 10);
			cout << "Student Grades and courses\n\n";
			SetConsoleTextAttribute(color, 7);
			cout << "Class 1: " << tempStudent[i].class1.code << "\tGrade: " << tempStudent[i].class1.studentGrade << "%" << "\tCost: $NZD" << tempStudent[i].class1.courseCost << endl;
			cout << "Class 2: " << tempStudent[i].class2.code << "\tGrade: " << tempStudent[i].class2.studentGrade << "%" << "\tCost: $NZD" << tempStudent[i].class2.courseCost << endl;
			cout << "Class 3: " << tempStudent[i].class3.code << "\tGrade: " << tempStudent[i].class3.studentGrade << "%" << "\tCost: $NZD" << tempStudent[i].class3.courseCost << endl;
			cout << "Class 4: " << tempStudent[i].class4.code << "\tGrade: " << tempStudent[i].class4.studentGrade << "%" << "\tCost: $NZD" << tempStudent[i].class4.courseCost << endl << endl;
			float totalPoints;
			totalPoints = (tempStudent[i].class1.studentGrade + tempStudent[i].class2.studentGrade + tempStudent[i].class3.studentGrade + tempStudent[i].class4.studentGrade) / 4;
			SetConsoleTextAttribute(color, 2);
			cout << "Grade average =                        " << totalPoints << "%" << endl;
			cout << "Total Semester Cost =                 $NZD " << tempStudent[i].class1.courseCost + tempStudent[i].class2.courseCost + tempStudent[i].class3.courseCost + tempStudent[i].class4.courseCost << endl;
			break;
		}

		else if (tempStudent[i].ID == IDsearch && tempStudent[i].Password != recPassword) {
			cout << "\n\nNo student with these credentials was found. If this continues, please verify your password with the administrator. \n\n";
			break;

		}
		else
		{
			break;
		}
	}

	SetConsoleTextAttribute(color, 7);
	cout << "\n\nPress 1 to return to the student database\n"; // returns to student database
	cout << "Press 2 to return to the main menu\n"; // returns to main menu
	cout << "Press 3 or anything else to EXIT the program\n";// EXIT
	int menuChoiceStudent;
	cout << "Enter your choice"; cin >> menuChoiceStudent;

	switch (menuChoiceStudent) {
	case 1:
		cout << "\n\nLogging out\nReturning to main menu...";
		Sleep(1000);
		studentDatabase(tempStudent);
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
void StudentGradeSum(vector<Student>& tempStudent) {
	//This function prints course grades.
	//Note, 90–100 A; 80–89 B; 70–79 C; 60–69 D; 50–59 E; 0–49 F
	system("cls");
	ShowHeader();
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	string IDsearch;
	string recPassword;
	SetConsoleTextAttribute(color, 14);
	cout << "                         Student Course Marks enquiry screen \n\n";
	SetConsoleTextAttribute(color, 7);
	cout << "Please re-confirm your student ID: "; cin >> IDsearch;
	cout << "Please re-confirm your password: "; cin >> recPassword;
	SetConsoleTextAttribute(color, 7);
	Student s;
	char searchChoice = 'n';
	int flag = 0;
	string line;
	string property;
	tempStudent = readFromFile();


	int i;
	for (i = 0; i < tempStudent.size(); i++) {

		if (tempStudent[i].ID != IDsearch) {
			cout << "\n\nNo student was found. Please verify your student ID.\n\n";    //check ID exists
			break;

		}
		else if (tempStudent[i].ID == IDsearch && tempStudent[i].Password == recPassword) {
			SetConsoleTextAttribute(color, 10);
			cout << "\nWelcome " << tempStudent[i].fName << " " << tempStudent[i].lName << endl;
			SetConsoleTextAttribute(color, 7);
			cout << "Thank you! Your ID " << tempStudent[i].ID << " and its associated password are now confirmed.\n";

			SetConsoleTextAttribute(color, 10);
			cout << "\nYour Current Semester's Student Fees\n";
			SetConsoleTextAttribute(color, 7);
			cout << "Accounting Class 1: " << tempStudent[i].class1.code << "\t" << tempStudent[i].class1.studentGrade << "%" << endl;
			cout << "Accounting Class 2: " << tempStudent[i].class2.code << "\t" << tempStudent[i].class2.studentGrade << "%" << endl;
			cout << "Accounting Class 3: " << tempStudent[i].class3.code << "\t" << tempStudent[i].class3.studentGrade << "%" << endl;
			cout << "Accounting Class 4: " << tempStudent[i].class4.code << "\t" << tempStudent[i].class4.studentGrade << "%" << endl;

			float totalPoints;
			totalPoints = (tempStudent[i].class1.studentGrade + tempStudent[i].class2.studentGrade + tempStudent[i].class3.studentGrade + tempStudent[i].class4.studentGrade) / 4;
			SetConsoleTextAttribute(color, 2);
			cout << "Grade average = " << totalPoints << "%" << endl;
			int MarkAve = totalPoints;
			//cout << "Your Overall Grade for the semester is: " << MarkAve << endl;
			cout << "This is an overall grade of ";

			if (MarkAve >= 90) { // 90 and above
				SetConsoleTextAttribute(color, 10);
				cout << "A. Excellent. You have obtained top marks this Semester. Truly well done!" << endl;
			}
			else if (80 <= MarkAve < 90) { //80-89
				SetConsoleTextAttribute(color, 10);
				cout << "B. Very well done." << endl;
			}
			else if (70 <= MarkAve < 80) { //70-79
				SetConsoleTextAttribute(color, 7);
				cout << "C. You have passed this semester." << endl;
			}
			else if (60 <= MarkAve < 70) { //60-69
				SetConsoleTextAttribute(color, 7);
				cout << "D. Overall pass but you may wish to go over some of the concepts again." << endl;
			}
			else if (50 <= MarkAve < 60) { //50-59
				SetConsoleTextAttribute(color, 10);
				cout << "E. Overall pass but you may wish to ask for extra tutoring." << endl;
			}
			else { //0-49
				SetConsoleTextAttribute(color, 12);
				cout << "F. It appears that you may have failed some papers. Please contact your lecturers for remedial tutoring." << endl;
			}
			break;




		}
		else if (tempStudent[i].ID == IDsearch && tempStudent[i].Password != recPassword) {
			cout << "\n\nNo student with these credentials was found.\n\n";
			break;
		}
		else
		{
			break;
		}
	}

	SetConsoleTextAttribute(color, 7);
	cout << "\n\nPress 1 to return to the student database\n"; // returns to student database
	cout << "Press 2 to return to the main menu\n"; // returns to main menu
	cout << "Press 3 or anything else to EXIT the program\n";// EXIT
	int menuChoiceStudent;
	cout << "Enter your choice"; cin >> menuChoiceStudent;

	switch (menuChoiceStudent) {
	case 1:
		cout << "\n\nLogging out\nReturning to main menu...";
		Sleep(1000);
		studentDatabase(tempStudent);
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
void studentTuitionSum(vector<Student>& tempStudent) {

	//This function prints a list of current course costs ONLY if both the ID and password match so other students cannot query for other people.
	system("cls");
	ShowHeader();
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	string IDsearch;
	string recPassword;
	SetConsoleTextAttribute(color, 14);
	cout << "                         Student course cost enquiry screen \n\n";
	SetConsoleTextAttribute(color, 7);
	cout << "Please re-confirm your student ID: "; cin >> IDsearch;
	cout << "Please re-confirm your password: "; cin >> recPassword;
	SetConsoleTextAttribute(color, 7);
	Student s;
	char searchChoice = 'n';
	int flag = 0;
	string line;
	string property;
	tempStudent = readFromFile();

	int i;
	for (i = 0; i < tempStudent.size(); i++) {
		if (tempStudent[i].ID != IDsearch) {
			cout << "\n\nNo student was found. Please verify your student ID.\n\n";    //check ID exists
			break;

		}
		else if (tempStudent[i].ID == IDsearch && tempStudent[i].Password == recPassword) {
			SetConsoleTextAttribute(color, 10);
			cout << "\nWelcome " << tempStudent[i].fName << " " << tempStudent[i].lName << endl;
			SetConsoleTextAttribute(color, 7);
			cout << "Thank you! Your ID " << tempStudent[i].ID << " and its associated password are now confirmed.\n";

			SetConsoleTextAttribute(color, 10);
			cout << "\nYour Current Semester's Student Fees\n";
			SetConsoleTextAttribute(color, 7);
			cout << "Accounting Class 1: " << tempStudent[i].class1.code << "\tCost: $NZD " << tempStudent[i].class1.courseCost << endl;
			cout << "Accounting Class 2: " << tempStudent[i].class2.code << "\tCost: $NZD " << tempStudent[i].class2.courseCost << endl;
			cout << "Accounting Class 3: " << tempStudent[i].class3.code << "\tCost: $NZD " << tempStudent[i].class3.courseCost << endl;
			cout << "Accounting Class 4: " << tempStudent[i].class4.code << "\tCost: $NZD " << tempStudent[i].class4.courseCost << endl;
			cout << "Total Semester Cost =                 $NZD " << tempStudent[i].class1.courseCost + tempStudent[i].class2.courseCost + tempStudent[i].class3.courseCost + tempStudent[i].class4.courseCost << endl;
			SetConsoleTextAttribute(color, 2);
			cout << "This is your current tuition for the semester. Thank you for your payments to date." << endl;
			cout << "If any queries please let us know.";
			break;
		}
		else if (tempStudent[i].ID == IDsearch && tempStudent[i].Password != recPassword) {
			cout << "\n\nNo student with these credentials was found.\n\n";
			break;
		}
		else
		{
			break;
		}
	}


	SetConsoleTextAttribute(color, 7);
	cout << "\n\nPress 1 to return to the student database\n"; // returns to student database
	cout << "Press 2 to return to the main menu\n"; // returns to main menu
	cout << "Press 3 or anything else to EXIT the program\n";// EXIT
	int menuChoiceStudent;
	cout << "Enter your choice"; cin >> menuChoiceStudent;

	switch (menuChoiceStudent) {
	case 1:
		cout << "\n\nLogging out\nReturning to main menu...";
		Sleep(1000);
		studentDatabase(tempStudent);
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


void studentAvailableCourses(vector<Student>& tempStudent) // this is case 5 in the main student area
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

	SetConsoleTextAttribute(color, 7);
	cout << "\n\nPress 1 to return to the student database\n"; // returns to student database
	cout << "Press 2 to return to the main menu\n"; // returns to main menu
	cout << "Press 3 or anything else to EXIT the program\n";// EXIT
	int menuChoiceStudent;
	cout << "Enter your choice"; cin >> menuChoiceStudent;

	switch (menuChoiceStudent) {
	case 1:
		cout << "\n\nLogging out\nReturning to main menu...";
		Sleep(1000);
		studentDatabase(tempStudent);
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

void endMenuchoise(vector<Student>& tempStudent) // this is for the student
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
		studentDatabase(tempStudent);
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
	cout << "---------------------------------------------------------------------------------------------";
	cout << endl << endl;
	SetConsoleTextAttribute(color, 15);
	return;
}