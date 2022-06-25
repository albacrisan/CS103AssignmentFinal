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
void viewStudentPersonaldetails(vector<Student>& tempStudent);
void studentDatabaseIN();
void StudentGradeSum(vector<Student>& tempStudent);
void studentTuitionSum(vector<Student>& tempStudent);
void studentAvailableCourses(vector<Student>& tempStudent);
void studentAvailableCourses(vector<Student>& tempStudent);
struct CourseRecord { // for the course info
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
		SetConsoleTextAttribute(color, 15);
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

}; // for the course info
void displayCourses(vector<CourseRecord>& courses) { // for the course info

	for (auto course : courses) {
		course.display();
	}
}  

//Headers and functionality
void ShowHeader();
void endMenuchoiseIN(vector<Student>& tempStudent);
void endMenuchoise(vector<Student>& tempStudent);

int main() {

	ShowHeader();

	system("color 0f");
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
	system("color 8b");
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
	default: 
		
		cout << "\n\n\n Invalid Selection. Press 1-5 to select a menu option ";
		Sleep(1000);
		adminDatabase(tempStudent);
	};
}



void studentSearch(vector<Student>& tempStudent) {
	system("cls");
	ShowHeader();
	system("color 8b");
	string IDsearch;
	
	cout << "           ***Student Search & Display***\n\n\n\n";
	
	cout << " Search for student by ID: "; cin >> IDsearch;
	Student s;
	char searchChoice = 'n';
	int flag = 0;
	string line;
	string property;
	int i;
	
	for (i = 0; i < tempStudent.size(); i++) {
		if (tempStudent[i].ID == IDsearch) {
			
			
			cout << "\n Student " << IDsearch << " found\n Loading student data...\n\n\n";
			Sleep(1000);
			system("color 1f");
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
	
	cout << " No student with ID: " << IDsearch << " was found\n";
	
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
	system("color 8b");
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
			system("color 3f");
			cout << "\n Invalid Input. Press x to return to main menu: ";
		}
	}
}

void classGradeAverages(vector<Student>& tempStudent) {
	system("cls");
	ShowHeader();
	system("color 8b");
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
	system("color 8b");
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
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	int menuChoice;
	string IDsearch;
	string recPassword;
	SetConsoleTextAttribute(color, 14);
	cout << "                         Student Database Access\n\n";
	SetConsoleTextAttribute(color, 15);
	cout << " Press 1 to access available actions for this current Semester\n";
	cout << " Press 2 to see all courses available next semester\n";// opens a list of all available courses next semester for a student
	cout << " Press 3 to log out to main\n\n";
	cout << "\n Enter your choice: "; cin >> menuChoice;

	switch (menuChoice) {
	case 1: studentDatabaseIN();
		break;
	case 2: studentAvailableCourses(tempStudent);
		break;
	case 3:
		cout << "\n\nLogging out\nReturning to main menu...";
		Sleep(1000);
		main();
	};

}


void studentDatabaseIN() {
	system("cls");
	ShowHeader();

	//Reload data
	vector <Student> tempStudent;
	tempStudent = readFromFile();
	system("cls");
	ShowHeader();
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	int menuChoice;
	string IDsearch;
	string recPassword;
	SetConsoleTextAttribute(color, 14);
	cout << "                   Student Database Access - Current Semester\n\n";
	SetConsoleTextAttribute(color, 15);
	cout << " Press 1 to view your Personal and Emergency Contact details\n";
	cout << " Press 2 to see your grade summary for the year\n";
	cout << " Press 3 to see tuition cost summary\n";
	cout << " Press 4 to log out to main\n\n";
	cout << " Enter your choice: "; cin >> menuChoice;

	switch (menuChoice) {
	case 1: viewStudentPersonaldetails(tempStudent);
		break;
	case 2: StudentGradeSum(tempStudent);
		break;
	case 3: studentTuitionSum(tempStudent);
		break;
	case 4:
		cout << "\n\nLogging out\nReturning to main menu...";
		Sleep(1000);
		main();
	};

}

void viewStudentPersonaldetails(vector<Student>& tempStudent) {

	system("cls");
	ShowHeader();
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 14);
	cout << "                         Student Personal details screen \n\n";
	string IDsearch;
	string recPassword;
	SetConsoleTextAttribute(color, 15);
	cout << " Search for student by ID: "; cin >> IDsearch;
	cout << " Search for student by password: "; cin >> recPassword;
	Student s;
	char searchChoice = 'n';
	int flag = 0;
	string line;
	string property;
	int i;

	for (i = 0; i < tempStudent.size(); i++) {
		if (tempStudent[i].ID == IDsearch && tempStudent[i].Password == recPassword) {
			system("cls");
			ShowHeader();
			HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(color, 14);
			cout << "                         Viewing personal details \n\n";
			
			SetConsoleTextAttribute(color, 10);
			cout << " - Personal Contact Details - \n\n";
			SetConsoleTextAttribute(color, 15);
			cout << " First Name:       " << tempStudent[i].fName << endl;
			cout << " Last Name:        " << tempStudent[i].lName << endl;
			cout << " Email Address:    " << tempStudent[i].email << endl << endl;

			SetConsoleTextAttribute(color, 10);
			cout << " - Emergency Contact Details -\n\n";
			SetConsoleTextAttribute(color, 15);
			cout << " First Name:       " << tempStudent[i].parent.fName << endl;
			cout << " Last Name:        " << tempStudent[i].parent.lName << endl;
			cout << " Contact Number:   " << tempStudent[i].parent.contactNumber << endl << endl;

			break;
		}
		else { SetConsoleTextAttribute(color, 12); "No record found"; }
	}
	
	endMenuchoiseIN(tempStudent);
}



void StudentGradeSum(vector<Student>& tempStudent) {
	//This function prints course grades.
	//Note, 90–100 A; 80–89 B; 70–79 C; 60–69 D; 50–59 E; 0–49 F
	system("cls");
	ShowHeader();
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 14);
	cout << "                         Student Course Marks enquiry screen \n\n";
	string IDsearch;
	string recPassword;
	SetConsoleTextAttribute(color, 15);
	cout << " Search for student by ID: "; cin >> IDsearch;
	cout << " Search for student by password: "; cin >> recPassword;
	Student s;
	char searchChoice = 'n';
	int flag = 0;
	string line;
	string property;
	int i;

	for (i = 0; i < tempStudent.size(); i++) {
		if (tempStudent[i].ID == IDsearch && tempStudent[i].Password == recPassword) {
			system("cls");
			ShowHeader();
			HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(color, 14);
			cout << "                         Viewing Course Mark details \n\n";

			SetConsoleTextAttribute(color, 10);
			cout << "\n - Your Current Semester's Marks - \n\n";
			SetConsoleTextAttribute(color, 15);
			cout << " Accounting Class 1: " << tempStudent[i].class1.code << " Accounting for Strategy and Value      \tMark: " << tempStudent[i].class1.studentGrade << "%" << endl;
			cout << " Accounting Class 2: " << tempStudent[i].class2.code << " Fraud Auditing                         \tMark: " << tempStudent[i].class2.studentGrade << "%" << endl;
			cout << " Accounting Class 3: " << tempStudent[i].class3.code << " Data Analytics for Financial Statements\tMark: " << tempStudent[i].class3.studentGrade << "%" << endl;
			cout << " Accounting Class 4: " << tempStudent[i].class4.code << " Accounting Information Systems         \tMark: " << tempStudent[i].class4.studentGrade << "%" << endl;

			SetConsoleTextAttribute(color, 10);
			cout << "\n - Overall mark - \n\n";
			SetConsoleTextAttribute(color, 15);
			double average;
			average = (tempStudent[i].class1.studentGrade + tempStudent[i].class2.studentGrade + tempStudent[i].class3.studentGrade + tempStudent[i].class4.studentGrade) / 4;
			cout << " In total your average was ";
			SetConsoleTextAttribute(color, 14); 
			cout << average << "%" << endl;
			SetConsoleTextAttribute(color, 15);
			int MarkAve = average;
			cout << " This is an overall grade of ";

			if (MarkAve >= 90) { // 90 and above
				SetConsoleTextAttribute(color, 10);
				cout << "A. Excellent. You have obtained top marks this Semester. Truly well done!" << endl;
			}
			else if (MarkAve >= 80 && MarkAve < 90) { //80-89
				SetConsoleTextAttribute(color, 10);
				cout << "B. Very well done." << endl;
			}
			else if (MarkAve >= 70 && MarkAve < 80) { //70-79
				SetConsoleTextAttribute(color, 7);
				cout << "C. You have passed this semester." << endl;
			}
			else if (MarkAve >= 60 && MarkAve < 70) { //60-69
				SetConsoleTextAttribute(color, 7);
				cout << "D. Overall pass but you may wish to go over some of the concepts again." << endl;
			}
			else if (MarkAve >= 50 && MarkAve < 60) { //50-59
				SetConsoleTextAttribute(color, 10);
				cout << "E. Overall pass but you may wish to ask for extra tutoring." << endl;
			}
			else { //0-49
				SetConsoleTextAttribute(color, 12);
				cout << "F. It appears that you may have failed some papers. \n Please contact your lecturers for remedial tutoring." << endl;
			}

			cout << " If you have any queries please let us know.\n\n";
			break;
		}
		else { SetConsoleTextAttribute(color, 12); "No record found\n\n"; }
	}

	endMenuchoiseIN(tempStudent);

}
void studentTuitionSum(vector<Student>& tempStudent) {

	//This function prints a list of current course costs ONLY if both the ID and password match so other students cannot query for other people.
	system("cls");
	ShowHeader();
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 14);
	cout << "                         Student course cost enquiry screen \n\n";
	string IDsearch;
	string recPassword;
	SetConsoleTextAttribute(color, 15);
	cout << " Search for student by ID: "; cin >> IDsearch;
	cout << " Search for student by password: "; cin >> recPassword;
	Student s;
	char searchChoice = 'n';
	int flag = 0;
	string line;
	string property;
	int i;

	for (i = 0; i < tempStudent.size(); i++) {
		if (tempStudent[i].ID == IDsearch && tempStudent[i].Password == recPassword) {
			system("cls");
			ShowHeader();
			HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(color, 14);
			cout << "                         Viewing Course Cost details \n\n";

			SetConsoleTextAttribute(color, 10);
			cout << "\n - Your Current Semester's Student Fees - \n\n";
			SetConsoleTextAttribute(color, 15);
			cout << " Accounting Class 1: " << tempStudent[i].class1.code << " Accounting for Strategy and Value      \tCost: $NZD " << tempStudent[i].class1.courseCost << endl;
			cout << " Accounting Class 2: " << tempStudent[i].class2.code << " Fraud Auditing                         \tCost: $NZD " << tempStudent[i].class2.courseCost << endl;
			cout << " Accounting Class 3: " << tempStudent[i].class3.code << " Data Analytics for Financial Statements\tCost: $NZD " << tempStudent[i].class3.courseCost << endl;
			cout << " Accounting Class 4: " << tempStudent[i].class4.code << " Accounting Information Systems         \tCost: $NZD " << tempStudent[i].class4.courseCost << endl;

			SetConsoleTextAttribute(color, 10);
			cout << "\n - Totals - \n\n";
			SetConsoleTextAttribute(color, 15);
			cout << " In total you have 4 papers.Your total Semester Cost =  ";
			SetConsoleTextAttribute(color, 14);
			cout << "$NZD " << tempStudent[i].class1.courseCost + tempStudent[i].class2.courseCost + tempStudent[i].class3.courseCost + tempStudent[i].class4.courseCost << endl;
			SetConsoleTextAttribute(color, 15);
			cout << " This is your current tuition for the semester. Thank you for your payments to date." << endl;
			cout << " If you have any queries please let us know.\n\n";
			break;
		}
		else { SetConsoleTextAttribute(color, 12); "No record found\n\n"; }
	}

	endMenuchoiseIN(tempStudent);
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


	SetConsoleTextAttribute(color, 15);
	Sleep(1000);

	SetConsoleTextAttribute(color, 15);
	cout << "Press 1 to return to the student database\n"; // returns to student database
	cout << "Press 2 to return to the main menu\n"; // returns to main menu
	cout << "Press 3 or anything else to EXIT the program\n\n";// EXIT
	int menuChoiceStudent;
	cout << "Enter your choice: "; cin >> menuChoiceStudent;

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
	cout << "Enter your choice: "; cin >> menuChoiceStudent;

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

void endMenuchoiseIN(vector<Student>& tempStudent) // this is for the student
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 14);
	cout << "Control Menu\n";
	SetConsoleTextAttribute(color, 15);
	cout << "Press 1 to return to the student database for this semester\n"; // returns to student database
	cout << "Press 2 to return to the main student database\n";
	cout << "Press 3 to return to the main Login menu\n"; // returns to main menu
	cout << "Press 4 or anything else to EXIT the program\n\n";// EXIT
	int menuChoiceStudent;
	cout << "Enter your choice: "; cin >> menuChoiceStudent;

	switch (menuChoiceStudent) {
	case 1:
		cout << "\n\nLogging out\nReturning to student database for current semester menu...";
		Sleep(1000);
		studentDatabaseIN();

	case 2:
		cout << "\n\nLogging out\nReturning to student database for current semester menu...";
		Sleep(1000);
		studentDatabase(tempStudent);
	case 3:
		cout << "\n\nLogging out\nReturning to main menu...";
		Sleep(1000);
		main();
	case 4:
		cout << "\n\nClosing App...";
		exit(1);
	default:
		cout << "\n\nClosing App.. As not 1, 2 or 3 - you have been logged out.";
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