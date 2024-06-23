#pragma once
#ifndef USER_H
#define USER_H
#include<iostream>
#include<fstream>
#include<string>
#include<exception>
#include<vector>
using namespace std;
class user
{
protected:
	string username;
	string password;
	int enterInt();
	double enterDouble();

public:

	virtual void showInfo();	//Show the basic information of the user, name, identity, etc. The basic information of each identity is different, so use the virtual function
	void showMenu();	//One method common to all three user identities
};

//This method is not used but it is still necessary to write a definition
void user::showInfo() {
	cout << "Your name: " << username << endl;
}

//The menu could be optimized
void user::showMenu() {
	cout << "\n";
	cout << "***********************************************************" << endl;
	cout << "                         " << "MENU" << "                    " << endl;
	cout << "***********************************************************" << endl;
	cout << "DishID\t\t\tDishName\t\tDishNumber" << endl;
	fstream fin("menu.txt", ios::in);
	char line[100];	//Menus with more than 100 characters in a line may have errors but are generally not a problem.
	while (!fin.eof()) {
		fin.getline(line, 100);
		cout << line << endl;
	}
	fin.close();
	cout << "***********************************************************" << endl;
}

//Let the user enter an integer
int user::enterInt() {
	string i;	//User-entered
	int integer = 0;	//The integer to return
	bool success = 0;	//Determine whether to enter a successful integer
	do {
		getline(cin, i);	//Collect user input
		if (i == "") {	//If the user hits the carriage return directly
			cout << "Please enter a correct integer" << endl;
			goto L1;
		}
		for (int j = 0; j < i.size(); j++) {
			if (isdigit(i.at(j)) == 0) {	//If one of the characters is not a number
				cout << "Please enter a correct integer" << endl;
				goto L1;
			}
		}
		success = 1;	//Enter integer successfully
	L1: continue;
	} while (success != 1);

	integer = atoi(i.c_str());	//string to int
	return integer;
}

//Let the user enter a decimal number
double user::enterDouble() {
	string d;	//User-entered
	double db = 0;
	bool success = 0;
	bool haveDp = 0;	//Decimal points have been detected
	do {
		haveDp = 0;
		getline(cin, d);	//Collect user input
		if (d == "") {	//If the user hits the carriage return directly
			cout << "Please enter a correct number" << endl;
			goto L2;
		}
		for (int i = 0; i < d.size(); i++) {
			//
			if (i == 0 || i == (d.size() - 1) || haveDp == 1) {
				if (isdigit(d.at(i)) == 0) {
					cout << "Please enter a correct number" << endl;
					goto L2;
				}
			}
			//At the beginning, or at the end, or if there has been a decimal point, then the decimal point cannot be entered
			else {
				if (isdigit(d.at(i)) == 0) {
					if (d.at(i) == '.') {
						haveDp == 1;
					}
					else {
						cout << "Please enter a correct number" << endl;
						goto L2;
					}
				}
			}
		}
		success = 1;
	L2: continue;
	} while (success != 1);

	db = atof(d.c_str());	//string to double
	return db;
}
#endif // !USER_H








