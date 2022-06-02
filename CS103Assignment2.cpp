// CS103Assignment2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <stdlib.h>
using namespace std;

struct universityClasses {
	string courseCode; //Three letters for course & 3 numbers: first 2 representing the year, 3rd the semester 1, 2 or 3 for summer school
	string courseName;
	int	teacherassigned;
	float cost;
};

struct teacher {
	int title;  //Mr  = 1, Mrs = 2, Miss = 3, Dr = 4; not super necessary, can remove
	string teacherFirstName;
	string teacherlastName;
	int teacherID;
	string teacherPassword;
};

struct Student {
	string studentFirstName;
	string studentlastName;
	int studentID;
	int studentPhoneNumber;
	int studentEmail;
	//string studentPassword, removed as we discussed student no access - if correct pls delete
	string parentFirstName; // Start of emergency contact details
	string parentlastName;
	long int parentPhoneNumber;
	string CoursesAssigned;
	bool courseCompleted; // “Y / N”
	bool paid; // “Y / N”;
	float SUM; // -Total tuition per semester / year
};



struct Grades {
	string courseCode;
	float averageAllStudentGradeperclass;
	char letterGrade;
	float averageOverallmark;  // will be result of a function
};


int main()
{
	//string admin_pass = "admin";
	//cout << "Enter the admin password: ";
	//string password;
	//cin >> password;

	cout << "Hello World!\n";
	cout << "Update by Matt\n";
}

// this is attempt with new branch