//Added name check function
//Optimized user interface

#include<iostream>
#include<fstream>
#include<string>
#include<exception>
#include<io.h>
#include "manager.h"
#include "chef.h"
#include "customer.h"
using namespace std;

enum ident { man, che, cus };	//Enumeration: Convenient to switch later


//Let the user enter an integer
int enterInt() {
	string i;	//User-entered
	int integer = 0;	//The integer to return
	bool success = 0;	//Whether or not to enter the integer that was just successful
	do {
		getline(cin, i);	//Collect user input
		if (i == "") {	//If the user hits the carriage return directly
			cout << "Please enter a correct integer" << endl;
			goto L1;
		}
		for (int j = 0; j < i.size(); j++) {
			if (isdigit(i.at(j)) == 0) {	//If one of the characters is not a interger number
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
double enterDouble() {
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
			//At the beginning, or at the end, or if there has been a decimal point, then the decimal point cannot be entered
			if (i == 0 || i == (d.size() - 1) || haveDp == 1) {
				if (isdigit(d.at(i)) == 0) {
					cout << "Please enter a correct number" << endl;
					goto L2;
				}
			}
			//Not at the beginning, not at the end, not over the decimal point, then you can enter the decimal point
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

//Check if there are spaces in a character array, return true to indicate that there are spaces
bool checkSpace(string str) {
	for (int i = 0; i < str.length(); i++) {
		if (str.at(i) == ' ') {
			return true;
		}
	}
	return false;
}


int main() {
	//Create all the txt files that the program will use
	string riFile = "registration_information.txt";
	string menuFile = "menu.txt";
	string orFile = "order_record.txt";
	string rmFile = "RawM.txt";
	string srFile = "shopRecord.txt";

	if (_access(riFile.c_str(), 0) != 0) {	//file not found
		fstream f;	//Streams to be used to create files
		f.open(riFile, ios::app);
		f.close();
	}

	if (_access(menuFile.c_str(), 0) != 0) {	//file not found
		fstream f;	//Streams to be used to create files
		f.open(menuFile, ios::app);
		f.close();
	}

	if (_access(orFile.c_str(), 0) != 0) {	//file not found
		fstream f;	//Streams to be used to create files
		f.open(orFile, ios::app);
		f.close();
	}

	if (_access(rmFile.c_str(), 0) != 0) {	//file not found
		fstream f;	//Streams to be used to create files
		f.open(rmFile, ios::app);
		f.close();
	}

	if (_access(srFile.c_str(), 0) != 0) {	//file not found
		fstream f;	//Streams to be used to create files
		f.open(srFile, ios::app);
		f.close();
	}

	int tempchoice; //User's Choice
	bool loginSuccess = 0;	//Determination of whether the login is successful
	bool usernameSuccess = 0; //Judgment of the success of entering the user name
	bool pwSuccess = 0; //Determination of successful password entry
	bool identitySuccess = 0;	//Judgment of whether the input identity is successful
	string username;	//username
	string password;	//password
	string identity;	//identity
	string tempname;	//Used to store the username in the file
	string temppw;	//Used to store passwords in files
	string tempidentity;	//Used to store user identities
	fstream fout;	//Output Stream
	fstream fin;	//input Stream

	// The following is the login screen
	do {
		//Adjustment of the login screen can be used as a template in the future
		cout << "\n \n \n" << endl;
		cout << "\t Please choose an option:\n" << endl;
		cout << "\t 1. Log in \n" << "\t 2. Register \n" << "\t 3. Exit" << endl;
		cout << "\n \n \n" << endl;
		tempchoice = enterInt();
		system("cls"); //Clean screen to maintain easy readability

		switch (tempchoice)
		{
		case 1:	//
			fin.open("registration_information.txt", ios::in);

			cout << "\n \n \n" << endl;
			cout << "\t enter user name: ";
			getline(cin, username);
			cout << "\t enter password: ";
			getline(cin, password);
			cout << "\n \n \n" << endl;

			while (!fin.eof()) {
				fin >> tempname >> temppw >> tempidentity;	//Pop up a line of user names and passwords to compare with what the user has entered (such an extraction will be done in spaces, with the first content reaching the end of the space and the second being the content after the space)
				if (tempname == username && temppw == password) {	//Matches the user's input
					cout << "log in successfully!" << endl;
					identity = tempidentity;	//Get the identity of this user
					loginSuccess = 1;		//Login successful
					fin.close();
					break;
				}
				if (fin.eof()) {	//If the user name and password are not matched by the end of the file, the login fails.
					cout << "log in failed!" << endl;
				}
			}
			fin.close();
			system("pause");	//clean the screen
			system("cls");
			break;
		case 2:	//Here write to the registry, the registration name and password can not contain spaces
			fout.open("registration_information.txt", ios::app);	//Write stream to registration information file

			//The following collection of usernames
			do {
				cout << "\n \n \n" << endl;
				cout << "\t user name (the length should be more than 3 and less than 8 characters, no space in the name): ";
				//Users cannot enter more than 8 characters and spaces
				getline(cin, username);

				//Performing a check
				fin.open("registration_information.txt", ios::in);
				while (!fin.eof()) {
					fin >> tempname >> temppw >> tempidentity;	//A line pops up with the username and password compared to what the user entered
					if (tempname == username) {	//Matches the user's input
						cout << "\n \n \n" << endl;
						cout << "repeated name!" << endl;
						fin.close();
						system("pause");	//clean the screen
						system("cls");
						goto label; //Jump to the next if's continue statement
					}
				}
				fin.close();

				if (username.length() > 8 || username.length() < 3) {
					cout << "\n \n \n" << endl;
					cout << "the user name must be within 3 to 8 characters! Please enter again." << endl;
					system("pause");	//clean
					system("cls");
				label:continue;	//Jump back to the conditional test of this while loop
				}
				if (checkSpace(username)) {
					cout << "\n \n \n" << endl;
					cout << "the user name cannot contain space! Please enter again" << endl;
					system("pause");	//clean
					system("cls");
					continue;	//Jump back to the conditional test of this while loop
				}
				usernameSuccess = 1;	//Username input successfully

			} while (usernameSuccess != 1);


			//Collect passwords below
			do {
				cout << "\t password (the length should be more than 3 and less than 8 characters, no space in the password):";
				//Users cannot enter more than 8 characters and spaces
				getline(cin, password);//Collect a full line of user input
				if (password.length() > 8 || password.length() < 3) {
					cout << "\t the password must be within 3 to 8 characters! Please enter again." << endl;
					system("pause");	//clean
					system("cls");
					continue;	//Jump back to the conditional test of this while loop
				}
				if (checkSpace(password)) {
					cout << "\t the password cannot contain space! Please enter again." << endl;
					system("pause");	//clean
					system("cls");
					continue;	//Jump back to the conditional test of this while loop
				}
				pwSuccess = 1;	//Password input successfully
				system("pause");
				system("cls");
			} while (pwSuccess != 1);


			//The following collection of identity
			do {
				cout << "\n \n \n" << endl;
				cout << "\t your identity (customer, chef, manager): ";
				//Users cannot enter more than 8 characters and spaces
				getline(cin, identity);
				if (!(identity == "customer" || identity == "chef" || identity == "manager")) {
					cout << "wrong identity!" << endl;
					system("pause");
					system("cls");
					continue;
				}
				identitySuccess = 1;	//Identity input successful
			} while (identitySuccess != 1);

			fout << username << "\t" << password << "\t" << identity << endl;
			fout.close();
			cout << "\n \n \n" << endl;
			cout << "register successfully!" << endl;
			system("pause");
			system("cls");	//Clean screen after successful registration
			break;

		case 3: //exit
			cout << "\n \n \n" << endl;
			cout << "\t Are you sure to EXIT? \n" << endl;
			cout << "\t 1 yes" << endl;
			cout << "\t 2 no" << endl;
			cout << "\n \n \n" << endl;
			tempchoice = enterInt();
			if (tempchoice == 1)
				return 0;//exit
			else
				system("cls");
			break;
		default:
			break;	//Unsuccessful, re-select the login registration option
		}
	} while (loginSuccess != 1);


	//Branching according to identity
	user* us; //There are two initializations that are not used here, and the corresponding instances are used depending on the switch
	ident iden;
	manager mana(username, password);
	chef cf(username, password);
	customer cust(username, password);
	if (identity == "manager") {
		iden = man;
	}
	else if (identity == "chef") {
		iden = che;
	}
	else {
		iden = cus;
	}
	//Start Branching
	switch (iden) {
	case 0:
		us = new manager(username, password);
		us->showInfo();
		mana.begin();
		break;

	case 1:
		us = new chef(username, password);
		us->showInfo();
		cf.begin();
		break;

	case 2:
		us = new customer(username, password);
		us->showInfo();
		us->showMenu();
		cust.begin();
		break;
	default:
		break;
	}

	return 0;
}

