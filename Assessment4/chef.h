#pragma once
#include "user.h" 

class chef : public user
{
protected:
	string identity = "chef";

public:
	chef(string name, string pw);
	void showInfo();
	void addMenu(); //add new dish
	void deleteMenu(); //delete the dish from the menu
	void changeMenu();//change the information of dish 
	void modifyMenu(); //a menu of which function does the user want to use to modify the dish list
	void showRawM(); //show the list of raw materials
	void begin();
};

chef::chef(string name, string pw) {
	username = name;
	password = pw;
}

void chef::showInfo() {
	cout << "Your name: " << username << "\t" << "Your identity is: " << identity << endl;
}

void chef::showRawM() {
	cout << "\n";
	cout << "***********************************************************" << endl;
	cout << "                     " << "Raw Materials" << "                " << endl;
	cout << "***********************************************************" << endl;
	cout << "Item\t\t\t\t\t\tItemNumber" << endl;
	fstream fin("RawM.txt", ios::in);
	char line[100];
	while (!fin.eof())
	{
		fin.getline(line, 100);
		cout << line << endl;
	}
	fin.close();
}

void chef::addMenu() {
	string addID; //the id of new dish
	string addname; // the name of new dish
	double addprice; // the price of new dish
	string ID; // record one id of exited dish
	string name;// record one name of exited dish
	double price;// record one price of exited dish
	cout << "Input the dish ID you want to add: ";
	getline(cin, addID);
	cout << "Input the dish name you want to add: ";
	getline(cin, addname);
	fstream fin("menu.txt", ios::in);
	while (!fin.eof()) { //check whether the dish id and name are repreated
		fin >> ID >> name >> price;
		if (ID == addID || name == addname) {
			cout << "The dish ID or name is repreated!" << endl;
			fin.close();
			return;//finish the function
		}
	}
	fin.close();

	cout << "Input the dish price you want to add: ";
	addprice = enterDouble();
	if (addprice < 0) {
		cout << "You input a wrong number!" << endl;
		return;//finish the function
	}
	fstream fout("menu.txt", ios::app); //Write the dish into menu file
	fout << addID;
	for (int j = 0; j < 24 - addID.size(); j++)
		fout << " ";
	fout << addname;
	for (int j = 0; j < 24 - addname.size(); j++)
		fout << " ";
	fout << addprice << endl;
	fout.close();
	cout << "Add the infomation successfully!" << endl;
}

void chef::deleteMenu() {
	string delID;
	string id;
	string name;
	double price;
	bool exitID = 0;// Used to determine if there is the id in the file to delete
	vector<string> dishID;
	vector<string> dishName;
	vector<double> dishPrice;
	cout << "Please input the id of dish you want to delete:" << endl;
	getline(cin, delID);

	fstream fin("menu.txt", ios::in);
	while (!fin.eof()) // store the information to the vector
	{
		fin >> id >> name >> price;
		dishID.push_back(id);
		dishName.push_back(name);
		dishPrice.push_back(price);
	}
	dishID.pop_back();
	dishName.pop_back();
	dishPrice.pop_back();

	if (dishID.size() == 0) {
		cout << "There is noting in the file." << endl;
		return;
	}
	if (dishID.size() <= 1) {
		if (delID == dishID[0]) {
			ofstream fout("menu.txt");
			fout.close();
			cout << "Delete successfully!" << endl;
		}
		else
		{
			cout << "Can't find it." << endl;
			return;
		}
	}
	else {
		for (int i = 0; i < dishID.size(); i++) { //delete the dish from vector
			if (dishID[i] == delID) {
				for (int pos = i; pos < dishID.size() - 1; pos++) {
					dishID[pos] = dishID[pos + 1];
					dishName[pos] = dishName[pos + 1];
					dishPrice[pos] = dishPrice[pos + 1];
				}
				dishID.pop_back();
				dishName.pop_back();
				dishPrice.pop_back();
				exitID = 1;
				cout << "Delete successfully!" << endl;
				break;
			}
		}
		fin.close();
		if (exitID == 0) { //If the dish does not exit, the function will finish
			cout << "Can't find the dish." << endl;
			return;
		}
		ofstream fout("menu.txt");
		for (int i = 0; i < dishID.size(); i++) {
			fout << dishID[i];
			for (int j = 0; j < 24 - dishID[i].size(); j++)
				fout << " ";
			fout << dishName[i];
			for (int j = 0; j < 24 - dishName[i].size(); j++)
				fout << " ";
			fout << dishPrice[i] << endl;
		}
		fout.close();
	}
}

void chef::changeMenu() {
	string changeID;
	string id;
	string name;
	double price;
	int position; //record the position of the dish need to change in the vector
	bool exitID = 0;//Used to determine if there is a id in the file to delete
	string changeName; //the new name of dish
	double changePrice; //the new priice of dish
	int choose; //let user to choose what they need to change
	vector<string> dishID;
	vector<string> dishName;
	vector<double> dishPrice;
	cout << "Please input the id of dish you want to change:" << endl;
	getline(cin, changeID);

	fstream fin("menu.txt", ios::in);
	while (!fin.eof())
	{
		fin >> id >> name >> price;
		dishID.push_back(id);
		dishName.push_back(name);
		dishPrice.push_back(price);
	}

	dishID.pop_back();
	dishName.pop_back();
	dishPrice.pop_back();

	for (int i = 0; i < dishID.size(); i++) { //find out the position of dish in the vector
		if (dishID[i] == changeID) {
			position = i;
			exitID = 1;
		}
	}
	fin.close();
	if (exitID == 0) {
		cout << "Can't find the dish." << endl;
		return;
	}
	cout << " What do you want to change?" << endl; // Let user to choose what they want to change
	cout << " 1. Change the name of dish. \n 2. Change the price of the dish. \n 3.Both name and price of the dish." << endl;
	choose = enterInt();
	switch (choose)
	{
	case 1:
		cout << "Input the new name of the dish: ";
		getline(cin, changeName);
		for (int i = 0; i < dishName.size(); i++) {
			if (dishName[i] == changeName) {
				cout << "The dish name has existed." << endl;
				return;
			}
		}
		dishName[position] = changeName;
		break;
	case 2:
		cout << "Input the new price of the dish: ";
		changePrice = enterDouble();
		dishPrice[position] = changePrice;
		break;
	case 3:
		cout << "Input the new name of the dish: ";
		getline(cin, changeName);
		cout << "Input the new price of the dish:";
		changePrice = enterDouble();
		dishName[position] = changeName;
		dishPrice[position] = changePrice;
		break;
	default:
		cout << "Input a wrong number." << endl;
		return;
		break;
	}
	ofstream fout("menu.txt"); //write the infomation of dish into menu file
	for (int i = 0; i < dishID.size(); i++) {
		fout << dishID[i];
		for (int j = 0; j < 24 - dishID[i].size(); j++)
			fout << " ";
		fout << dishName[i];
		for (int j = 0; j < 24 - dishName[i].size(); j++)
			fout << " ";
		fout << dishPrice[i] << endl;
	}
	fout.close();
	cout << "Change the infomation successfully!" << endl;
}

void chef::modifyMenu() {
	cout << "Which option do you want to choose?" << endl;
	cout << "1. Add dish" << endl;
	cout << "2. Delete dish" << endl;
	cout << "3. Change the information of dish" << endl;
	int choose;
	choose = enterInt();
	switch (choose)
	{
	case 1:
		addMenu();
		break;
	case 2:
		deleteMenu();
		break;
	case 3:
		changeMenu();
		break;
	default:
		cout << "You input a wrong number." << endl;
		break;
	}
}

void chef::begin() {
	int choose;
	int ifExit = 0;
	do {
		cout << "\n \n \n" << endl;
		cout << "Which service do you want to choose?";
		cout << "\n\t1. Check raw materials \n\t2. Check menu \n\t3. Modify menu \n\t4. Exit." << endl;
		cout << "\n \n \n" << endl;
		cin >> choose;
		cin.get();
		switch (choose)
		{
		case 1:
			showRawM();
			system("pause");
			system("cls");	//end, clean
			break;
		case 2:
			showMenu();
			system("pause");
			system("cls");	//end, clean
			break;
		case 3:
			modifyMenu();
			system("pause");
			system("cls");	//end, clean
			break;
		case 4:
			ifExit = 1;
			break;
		default:
			cout << "Please choose from the given options" << endl;
			system("pause");
			system("cls");
			break;
		}

	} while (ifExit == 0);
}


