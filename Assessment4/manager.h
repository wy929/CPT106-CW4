#pragma once
#include "user.h" 

class manager : public user
{
private:

protected:
	string identity = "manager";

public:
	manager(string name, string pw);
	void showInfo();
	void begin(); //The begin of manager class, has many choice for user to choose which function do they want to use

	void showRawM(); //show the raw material list
	void addRawM(); // add new raw material 
	void deleteRawM(); //delete the raw material from the list
	void changeRawM(); //change the raw material information
	void modifyRawM(); //A menu of which functions for users to choose which function of modify the raw list they want to use

	void addMenu(); //add new dish
	void deleteMenu(); //delete the dish from the menu
	void changeMenu();//change the information of dish 
	void modifyMenu(); //a menu of which function does the user want to use to modify the dish list


	void showShopRecord(); //show the shop record list
	void addShopRecord(); //add new shop record to the list
	void deleteShopRecord(); //delete the shop record from the list
	void changeShopRecord(); // change the shop record information in the list
	void modifyShopRecord(); //a menu of which function does the user want to use to modify the shop record information list

	void showUserInfo(); //show the user information
	void changeUserInfo(); // change the user information in the list
	void addUser(); // add new user information to the list
	void deleteUser(); // delete the user information from the list
	void modifyUserInfo(); // a menu of which function does the user want to use to modify the user information list

	void totalProfit();// calculate the current total profit
	void grossProfit(); // calculate the gross profit

	void showOrderRecord(); // show the order record list
	void changeOrderRecord(); // change the order record list
	void deleteOrderRecord(); //delete the order record list
};

manager::manager(string name, string pw) {
	username = name;
	password = pw;
}

void manager::showInfo() {
	cout << "Your name: " << username << "\t" << "Your identity is: " << identity << endl;
}

///Operating the raw material list
void manager::showRawM() {
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

void manager::addRawM() {
	string addName; //The name of the raw material that will add to the list
	int addnumber; // The number of the raw material will add to the list
	string name; //The name of raw material 
	string number; // The number of raw material
	cout << "Input the raw name you want to add: ";
	getline(cin, addName);
	fstream fin("RawM.txt", ios::in); //input the new raw material name and check if it exists
	while (!fin.eof()) {
		fin >> name >> number;
		if (name == addName) {
			cout << "The raw has exited." << endl;
			fin.close();
			return;//Finish this function
		}
	}
	fin.close();
	cout << "Input the raw material number you want to add: ";
	addnumber = enterInt(); //Let user input the number of raw material
	fstream fout("RawM.txt", ios::app); //Write the new raw material information to the text file
	fout << addName;
	for (int j = 0; j < 48 - addName.size(); j++)
		fout << " ";
	fout << addnumber << endl;
	fout.close();
	cout << "Add the infomation successfully!" << endl;
}

void manager::deleteRawM() {
	string delname; //The name of the raw material that will delete from the list
	string name;
	int number;
	bool exitName = 0;//Used to determine if there is a name in the file to delete
	vector<string> rawName; //A vector used to the record each raw material name
	vector<int> rawNum; //A vector used to record the number of each raw material
	cout << "Please input the name of raw materials you want to deldete:" << endl;
	getline(cin, delname);

	fstream fin("RawM.txt", ios::in);
	while (!fin.eof())//store all information from the file to the vectors
	{
		fin >> name >> number;
		rawName.push_back(name);
		rawNum.push_back(number);
	}
	rawName.pop_back();
	rawNum.pop_back();

	if (rawName.size() == 0) {
		cout << "There is noting in the file." << endl;
		return;
	}
	if (rawName.size() <= 1) {
		if (delname == rawName[0]) {
			ofstream fout("RawM.txt");
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
		for (int i = 0; i < rawName.size(); i++) { //delete the raw material from vector
			if (rawName[i] == delname) {
				for (int pos = i; pos < rawName.size() - 1; pos++) {
					rawName[pos] = rawName[pos + 1];
					rawNum[pos] = rawNum[pos + 1];
				}
				rawName.pop_back();
				rawNum.pop_back();
				exitName = 1;
				cout << "Delete " << delname << " successfully" << endl;
				break;
			}
		}
		fin.close();
		if (exitName == 0) {
			cout << "Can't find the raw materials." << endl;
			return;
		}
		ofstream fout("RawM.txt"); //Write the raw material into file
		for (int i = 0; i < rawName.size(); i++) {
			fout << rawName[i];
			for (int j = 0; j < 48 - rawName[i].size(); j++)
				fout << " ";
			fout << rawNum[i] << endl;
		}
		fout.close();
	}
}

void manager::changeRawM() {
	string changeRaw;//the name of raw material need to be changed
	string name;//record the raw material name in the file
	int changeNum; //the number of raw material will change to
	int number;
	int position; //Record the position of the raw material in the vector need to be change
	bool exitName = 0;
	vector<string> rawName;
	vector<int> rawNum;
	cout << "Please input the name of raw materials you want to deldete:" << endl;
	getline(cin, changeRaw);

	fstream fin("RawM.txt", ios::in);
	while (!fin.eof())//store all information from the file to the vectors
	{
		fin >> name >> number;
		rawName.push_back(name);
		rawNum.push_back(number);
	}

	rawName.pop_back();
	rawNum.pop_back();

	for (int i = 0; i < rawName.size(); i++) { //Find out the position of raw material in the vector
		if (rawName[i] == changeRaw) {
			position = i;
			exitName = 1;
			break;
		}
	}
	fin.close();

	if (exitName == 0) {
		cout << "Can't find the raw." << endl;
		return;
	}
	cout << "Input the raw materials number do you want to change: ";
	changeNum = enterInt();
	rawNum[position] = changeNum;

	ofstream fout("RawM.txt"); //Write the raw material into file
	for (int i = 0; i < rawName.size(); i++) {
		fout << rawName[i];
		for (int j = 0; j < 48 - rawName[i].size(); j++)
			fout << " ";
		fout << rawNum[i] << endl;
	}
	fout.close();
	cout << "Change the infomation successfully!" << endl;
}

void manager::modifyRawM() {
	cout << "Which option do you want to choose?" << endl;
	cout << "1. Add raw" << endl;
	cout << "2. Delete raw" << endl;
	cout << "3. Change the number of raw" << endl;
	int choose;
	choose = enterInt();
	switch (choose)
	{
	case 1:
		addRawM();
		break;
	case 2:
		deleteRawM();
		break;
	case 3:
		changeRawM();
		break;
	default:
		break;
	}
}

///Operating the menu list
void manager::addMenu() {
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

void manager::deleteMenu() {
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
		cout << "There is nothing in the file." << endl;
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

void manager::changeMenu() {
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

void manager::modifyMenu() {
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

///Operating the shop record list, most of the function are similar with the function of operating the menu
void manager::showShopRecord() {
	fstream fin("shopRecord.txt", ios::in);
	char line[100];
	cout << "\n";
	cout << "***********************************************************" << endl;
	cout << "                     " << "SHOPPING RECORD" << "                " << endl;
	cout << "***********************************************************" << endl;
	cout << "Item\t\t\t\t\t\tItemNumber" << endl;
	while (!fin.eof())
	{
		fin.getline(line, 100);
		cout << line << endl;
	}
	fin.close();
}

void manager::addShopRecord() {
	string addName; //the new name of the material bought by manager
	double cost; // the cost of this shopping
	cout << "Input the raw materials name you want to add: ";
	getline(cin, addName);
	cout << "Input the shop cost: ";
	cost = enterDouble();

	fstream fout("shopRecord.txt", ios::app);
	fout << addName;
	for (int j = 0; j < 48 - addName.size(); j++)
		fout << " ";
	fout << cost << endl;
	fout.close();
	cout << "Add the infomation successfully!" << endl;
}

void manager::deleteShopRecord() {
	string delname; // the name need to be deleted from the list
	string name; // record the name in the list
	double cost; //record the cost in the list
	bool exitName = 0;
	vector<string> recordName;
	vector<int> recordCost;
	cout << "Please input the name of shop record you want to deldete:" << endl;
	getline(cin, delname);

	fstream fin("shopRecord.txt", ios::in);
	while (!fin.eof())
	{
		fin >> name >> cost;
		recordName.push_back(name);
		recordCost.push_back(cost);
	}
	recordName.pop_back();
	recordCost.pop_back();

	if (recordName.size() == 0) {
		cout << "There is noting in the file." << endl;
		return;
	}
	if (recordName.size() <= 1) {
		if (delname == recordName[0]) {
			ofstream fout("shopRecord.txt");
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
		for (int i = 0; i < recordName.size(); i++) {//delete
			if (recordName[i] == delname) {
				for (int pos = i; pos < recordName.size() - 1; pos++) {
					recordName[pos] = recordName[pos + 1];
					recordCost[pos] = recordCost[pos + 1];
				}
				recordName.pop_back();
				recordCost.pop_back();
				exitName = 1;
				cout << "Delete  successfully" << endl;
				break;
			}
		}
		fin.close();
		if (exitName == 0) {
			cout << "Can't find this shop record." << endl;
			return;
		}
		ofstream fout("shopRecord.txt");
		for (int i = 0; i < recordName.size(); i++) {
			fout << recordName[i];
			for (int j = 0; j < 48 - recordName.size(); j++)
				fout << " ";
			fout << recordCost[i] << endl;
		}
		fout.close();
	}
}

void manager::changeShopRecord() {
	string delname;
	string name;
	double cost;
	bool exitName = 0;
	int count = 0;
	int recordNum;
	int position;
	vector<string> recordName;
	vector<int> recordCost;
	cout << "Please input the name of shop record you want to deldete:";
	getline(cin, delname);

	fstream fin("shopRecord.txt", ios::in);
	while (!fin.eof())
	{
		fin >> name >> cost;
		recordName.push_back(name);
		recordCost.push_back(cost);
	}
	recordName.pop_back();
	recordCost.pop_back();
	cout << "Input which shop record do you want to change: ";
	recordNum = enterInt();
	for (int i = 0; i < recordName.size(); i++) {
		if (recordName[i] == delname) {
			count++;
			exitName = 1;
		}
		if (count == recordNum) {
			position = i;
		}
	}
	fin.close();
	if (recordNum <= 0 || recordNum > count) {
		cout << "You input a wrong order number." << endl;
		return;
	}
	if (exitName == 0) {
		cout << "Can't find the shop record." << endl;
		return;
	}

	cout << "Input the new cost of that shop record:";
	cost = enterDouble();
	if (cost < 0) {
		cout << "You input a wrong number." << endl;
		return;
	}
	recordCost[position] = cost;
	ofstream fout("shopRecord.txt");
	for (int i = 0; i < recordName.size(); i++) {
		fout << recordName[i];
		for (int j = 0; j < 48 - recordName.size(); j++)
			fout << " ";
		fout << recordCost[i] << endl;
	}
	fout.close();
	cout << "Change the information successfully!" << endl;
}

void manager::modifyShopRecord() {
	cout << "Which option do you want to choose?" << endl;
	cout << "1. Add shop record." << endl;
	cout << "2. Delete shop record." << endl;
	cout << "3. Change shop record." << endl;
	int choose;
	choose = enterInt();
	switch (choose)
	{
	case 1:
		addShopRecord();
		break;
	case 2:
		deleteShopRecord();
		break;
	case 3:
		changeShopRecord();
		break;
	default:
		break;
	}
}

///Operating the user information list, most of the function are similar with the function of operating the menu
void manager::showUserInfo() {
	cout << "\n";
	cout << "**********************************************************************" << endl;
	cout << "                         " << "User Info" << "                  " << endl;
	cout << "**********************************************************************" << endl;
	cout << "UserName\t\tUserPassword\t\t\tUserIdentity" << endl;
	fstream fin("registration_information.txt", ios::in);
	char line[100];
	while (!fin.eof())
	{
		fin.getline(line, 100);
		cout << line << endl;
	}
	fin.close();
}
void manager::addUser() {
	string addName; //the new user name
	string addPW; //the password of this new user
	string addIden; //the identity of this new user
	string name; //store the name in the file
	string PW; // store the password in the file
	string iden; // store the indentity in the file
	int identitySuccess = 0; //To check if it is successful to input the identity
	cout << "Input the user name you want to add: ";
	getline(cin, addName);
	fstream fin("registration_information.txt", ios::in);
	while (!fin.eof()) {
		fin >> name >> PW >> iden;
		if (name == addName) {
			cout << "The user has exited." << endl;
			fin.close();
			return;
		}
	}
	fin.close();
	cout << "Input the password of the user: ";
	getline(cin, PW);

	do { //If the user don't input the correct identity, he needs to input again
		cout << "Input the identity of the user: ";
		cin >> addIden;
		if (!(addIden == "customer" || addIden == "chef" || addIden == "manager")) {
			cout << "wrong identity!" << endl;
			continue;
		}
		identitySuccess = 1;	//input the identity successfully
	} while (identitySuccess != 1);

	fstream fout("registration_information.txt", ios::app);
	fout << addName;
	for (int j = 0; j < 24 - addName.size(); j++)
		fout << " ";
	fout << PW;
	for (int j = 0; j < 32 - PW.size(); j++)
		fout << " ";
	fout << addIden << endl;

	fout.close();
	cout << "Add the infomation successfully!" << endl;
}
void manager::deleteUser() {
	string delName;
	string name;
	string PW;
	string iden;
	bool exitName = 0;
	vector<string> userName;
	vector<string> userPW;
	vector<string> userIden;
	cout << "Please input the user name you want to deldete:" << endl;
	getline(cin, delName);

	fstream fin("registration_information.txt", ios::in);
	while (!fin.eof())
	{
		fin >> name >> PW >> iden;
		userName.push_back(name);
		userPW.push_back(PW);
		userIden.push_back(iden);
	}
	int size = userName.size();
	if (size >= 2) {
		if (userName[size - 1] == userName[size - 2]) {
			userName.pop_back();
			userPW.pop_back();
			userIden.pop_back();
		}
	}

	if (userName.size() == 0) {
		cout << "There is noting in the file." << endl;
		return;
	}
	if (userName.size() <= 1) {
		if (delName == userName[0]) {
			ofstream fout("registration_information.txt");
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
		for (int i = 0; i < userName.size(); i++) {
			if (userName[i] == delName) {
				for (int pos = i; pos < userName.size() - 1; pos++) {
					userName[pos] = userName[pos + 1];
					userPW[pos] = userPW[pos + 1];
					userIden[pos] = userIden[pos + 1];
				}
				userName.pop_back();
				userPW.pop_back();
				userIden.pop_back();
				exitName = 1;
				cout << "Delete successfully!" << endl;
				break;
			}
		}
		fin.close();
		if (exitName == 0) {
			cout << "Can't find the raw materials." << endl;
			return;
		}
		ofstream fout("registration_information.txt");
		for (int i = 0; i < userName.size(); i++) {
			fout << userName[i];
			for (int j = 0; j < 24 - userName[i].size(); j++)
				fout << " ";
			fout << userPW[i];
			for (int j = 0; j < 24 - userPW[i].size(); j++)
				fout << " ";
			fout << userIden[i] << endl;
		}
		fout.close();
	}
}
void manager::changeUserInfo() {
	string changeName; //The new user name 
	string name;
	string PW;
	string iden;
	bool exitName = 0;
	int position;
	int identitySuccess = 0;
	vector<string> userName;
	vector<string> userPW;
	vector<string> userIden;
	cout << "Please input the user name you want to change:" << endl;
	getline(cin, changeName);

	fstream fin("registration_information.txt", ios::in);
	while (!fin.eof())
	{
		fin >> name >> PW >> iden;
		userName.push_back(name);
		userPW.push_back(PW);
		userIden.push_back(iden);
	}

	int size = userName.size();
	if (size >= 2) {
		if (userName[size - 1] == userName[size - 2]) {
			userName.pop_back();
			userPW.pop_back();
			userIden.pop_back();
		}
	}

	for (int i = 0; i < userName.size(); i++) {
		if (userName[i] == changeName) {
			position = i;
			exitName = 1;
			break;
		}
	}
	fin.close();
	if (exitName == 0) {
		cout << "Can't find the user." << endl;
		return;
	}

	cout << "Input the new password of the user: ";
	getline(cin, PW);
	do {
		cout << "Input the identity of the user: ";
		cin >> iden;
		if (!(iden == "customer" || iden == "chef" || iden == "manager")) {
			cout << "wrong identity!" << endl;
			continue;
		}
		identitySuccess = 1;
	} while (identitySuccess != 1);
	userPW[position] = PW;
	userIden[position] = iden;

	ofstream fout("registration_information.txt");
	for (int i = 0; i < userName.size(); i++) {
		fout << userName[i];
		for (int j = 0; j < 24 - userName[i].size(); j++)
			fout << " ";
		fout << userPW[i];
		for (int j = 0; j < 24 - userPW[i].size(); j++)
			fout << " ";
		fout << userIden[i] << endl;
	}
	fout.close();
	cout << "Change the infomation successfully!" << endl;
}

void manager::modifyUserInfo() {
	cout << "Which option do you want to choose?" << endl;
	cout << "1. Add user" << endl;
	cout << "2. Delete user" << endl;
	cout << "3. Change the information of user" << endl;
	int choose;
	choose = enterInt();
	switch (choose)
	{
	case 1:
		addUser();
		break;
	case 2:
		deleteUser();
		break;
	case 3:
		changeUserInfo();
		break;
	default:
		cout << "You input a wrong number." << endl;
		break;
	}
}

///Calculate the total and gross profit
void manager::totalProfit() {
	double totalprofit = 0;//record the total profit
	double totalfee;//record the cost of each user
	string username;
	fstream fin("order_record.txt", ios::in);
	while (!fin.eof()) { // calculate the total profit
		fin >> username >> totalfee;
		totalprofit = totalprofit + totalfee;
	}
	totalprofit = totalprofit - totalfee;
	cout << "The total profit is \t" << totalprofit << endl;
	fin.close();
}
void manager::grossProfit() {
	double totalprofit = 0;//record the total profit
	double totalfee;//record the cost of each user
	double costfee; //record the cost of buying raw material each time
	double totalcost = 0;//record the total cost of buying material 
	double grosspro;//record the gross profit
	string username;
	string rawName;
	fstream fin("order_record.txt", ios::in);
	while (!fin.eof()) { //calculate the total profit
		fin >> username >> totalfee;
		totalprofit = totalprofit + totalfee;
	}
	totalprofit = totalprofit - totalfee;
	fin.close();

	fstream finCost("shopRecord.txt", ios::in);
	while (!finCost.eof()) { // calculate the total cost
		finCost >> rawName >> costfee;
		totalcost = totalcost + costfee;
	}
	totalcost = totalcost - costfee;
	finCost.close();

	cout << "The total cost of raw materials is\t" << totalcost << endl;
	grosspro = totalprofit - totalcost; // calculate the gross profit
	cout << "The gross profit is\t" << grosspro << endl;
}

///Operating the order recordlist
void manager::showOrderRecord() {
	cout << "\n";
	cout << "***********************************************************" << endl;
	cout << "                     " << "Bill Record" << "                " << endl;
	cout << "***********************************************************" << endl;
	cout << "Name\t\t\t\t\t\tFee" << endl;
	fstream fin("order_record.txt", ios::in);
	char line[100];
	while (!fin.eof())
	{
		fin.getline(line, 100);
		cout << line << endl;
	}
	fin.close();
}
void manager::changeOrderRecord() {
	string changeUser; //record the new user name
	string name;  //record the user name in the file
	double fee; //record the cost of that user in the file
	bool exitName = 0;//Used to determine if there is a name in the file to delete
	int orderNum; //used to record which order the user want to change
	int count = 0;
	int position; // record the position of that order in the vector
	vector<string> userName;
	vector<double> userfee;
	cout << "Please input the user name you want to change:" << endl;
	getline(cin, changeUser);

	fstream fin("order_record.txt", ios::in);
	while (!fin.eof())
	{
		fin >> name >> fee;
		userName.push_back(name);
		userfee.push_back(fee);
	}
	userName.pop_back();
	userfee.pop_back();

	cout << "Input which order do you want to change: "; // Let user enter the number of oerder he want to change
	orderNum = enterInt();
	for (int i = 0; i < userName.size(); i++) {
		if (userName[i] == changeUser) {
			count++;
			exitName = 1;
		}
		if (count == orderNum) {
			position = i;
		}
	}

	fin.close();
	if (exitName == 0) {
		cout << "Can't find the consumer." << endl;
		return;
	}

	if (orderNum <= 0 || orderNum > count) {
		cout << "You input a wrong order number." << endl;
		return;
	}

	cout << "Input the new fee of the consumer: ";
	fee = enterDouble();
	userfee[position] = fee;

	ofstream fout("order_record.txt");
	for (int i = 0; i < userName.size(); i++) {
		fout << userName[i];
		for (int j = 0; j < 48 - userName[i].size(); j++)
			fout << " ";
		fout << userfee[i] << endl;
	}
	fout.close();
	cout << "Change the infomation successfully!" << endl;
}
void manager::deleteOrderRecord() {
	string delUser;
	string name;
	double fee;
	bool exitName = 0;
	int orderNum;
	int count = 0;
	int position;
	vector<string> userName;
	vector<double> userfee;
	cout << "Please input the user name you want to change:" << endl;
	getline(cin, delUser);

	fstream fin("order_record.txt", ios::in);
	while (!fin.eof())
	{
		fin >> name >> fee;
		userName.push_back(name);
		userfee.push_back(fee);
	}
	userName.pop_back();
	userfee.pop_back();

	cout << "Input which order do you want to delete: ";
	orderNum = enterInt();
	for (int i = 0; i < userName.size(); i++) {
		if (userName[i] == delUser) {
			count++;
			exitName = 1;
		}
		if (count == orderNum) {
			position = i;
		}
	}

	fin.close();
	if (exitName == 0) {
		cout << "Can't find the consumer." << endl;
		return;
	}

	if (orderNum <= 0 || orderNum > count) {
		cout << "You input a wrong order number." << endl;
		return;
	}

	if (userName.size() == 0) {
		cout << "There is noting in the file." << endl;
		return;
	}
	if (userName.size() <= 1) {
		if (delUser == userName[0]) {
			ofstream fout("order_record.txt");
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
		for (int pos = position; pos < userName.size() - 1; pos++) {
			userName[pos] = userName[pos + 1];
			userfee[pos] = userfee[pos + 1];
		}
		userName.pop_back();
		userfee.pop_back();
		cout << "Delete successfully!" << endl;

		ofstream fout("order_record.txt");
		for (int i = 0; i < userName.size(); i++) {
			fout << userName[i];
			for (int j = 0; j < 48 - userName[i].size(); j++)
				fout << " ";
			fout << userfee[i] << endl;
		}
		fout.close();
		cout << "Delete the infomation successfully!" << endl;
	}
}

void manager::begin() {
	int choose;
	int ifExit = 0;
	do {
		cout << "Which service do you want to choose?" << endl;
		cout << " \n\t1. Check raw materials \n\t2. Modify raw materials information \n\t3. Check menu \n\t4. Modify menu \n\t5. Check shopping list \n\t6. Modify shopping list";
		cout << "\n\t7. Check user infomation \n\t8. Modify user information \n\t9. Calculate total revenue \n\t10. Calculate gross profit \n\t11. Check bill records \n\t12. Change bill records\n\t13. Delete bill record. \n\t14.Exit." << endl;
		choose = enterInt();
		switch (choose)
		{
		case 1:
			showRawM();
			system("pause");
			system("cls");	//display over, clean
			showInfo();
			break;
		case 2:
			modifyRawM();
			system("pause");
			system("cls");	//display over, clean
			showInfo();
			break;
		case 3:
			showMenu();
			system("pause");
			system("cls");	//display over, clean
			showInfo();
			break;
		case 4:
			modifyMenu();
			system("pause");
			system("cls");	//display over, clean
			showInfo();
			break;
		case 5:
			showShopRecord();
			system("pause");
			system("cls");	//display over, clean
			showInfo();
			break;
		case 6:
			modifyShopRecord();
			system("pause");
			system("cls");	//display over, clean
			showInfo();
			break;
		case 7:
			showUserInfo();
			system("pause");
			system("cls");	//ÏÔÊ¾½áÊø£¬ÇåÆÁ
			showInfo();
			break;
		case 8:
			modifyUserInfo();
			system("pause");
			system("cls");	//display over, clean
			showInfo();
			break;
		case 9:
			totalProfit();
			system("pause");
			system("cls");	//display over, clean
			showInfo();
			break;
		case 10:
			grossProfit();
			system("pause");
			system("cls");	//display over, clean
			showInfo();
			break;
		case 11:
			showOrderRecord();
			system("pause");
			system("cls");	//display over, clean
			showInfo();
			break;
		case 12:
			changeOrderRecord();
			system("pause");
			system("cls");	//display over, clean
			showInfo();
			break;
		case 13:
			deleteOrderRecord();
			system("pause");
			system("cls");	//display over, clean
			showInfo();
			break;
		case 14:
			ifExit = 1;
			break;
		default:
			cout << "Please choose from the given options" << endl;
			break;
		}

	} while (ifExit == 0);
}