#pragma once
#include "user.h" 

class customer : public user
{
private:
	//The elements in these three vectors correspond one-to-one
	vector<string> dishid;	//store the id of each dish
	vector<string> dish;	//store the name of each dish
	vector<int> dishnum;	//store the number of each dish
	bool repeatID(string id);	//check if an id is repeated with dishid. If it is repeated, return true.
	double totalFee();	//calculate the current total fee

public:
	customer(string name, string pw);	//constructor
	void showInfo();	//show the information of the customer
	void showOrder();	//Display the customer's current order, including id, name, number of servings
	void addOrder();	//Let the user enter the id of the dish, the number of servings, 
						//and then add the corresponding attributes of the dish to the three vectors
						//duplicate ids are not allowed to be added
	void begin();		//Let users choose what to do
	void modOrder();	//Let the user enter the id of the dish to be modified
						//Then enter a new id, the number of servings
						//change the corresponding values in the three vectors
	void deleteOrder();	//Let the user enter an id to be deleted and delete it from the vectors
	void checkout();	//This restaurant does not upload orders to chefs until after checkout
						//Tell the customer the total amount to be paid at the checkout and the customer choose whether to pay
						//After payment, write the three vectors to the order record, and then empty the three vectors

};

//constructor
customer::customer(string name, string pw) {
	username = name;
	password = pw;
}

void customer::showInfo() {
	cout << "Your name: " << username << "\t" << "Your identity is: customer" << endl;
}

void customer::showOrder() {
	cout << "-----------------------------------------------------------" << endl;
	cout << "The dish you have ordered is: \n" << endl;
	cout << "DishID\t\t\tDishName\t\tDishNumber" << endl;
	//show the dishes in the order, according to the three vectors
	for (int i = 0; i < dishid.size(); i++) {

		cout << dishid[i];
		for (int j = 0; j < 24 - dishid[i].size(); j++)
			cout << " ";
		cout << dish[i];
		for (int j = 0; j < 24 - dish[i].size(); j++)
			cout << " ";
		cout << dishnum[i] << endl;

	}
	//display the total price
	cout << "\nThe total price is: " << totalFee() << "$" << endl;
	cout << "-----------------------------------------------------------" << endl;
	system("pause");
}

bool customer::repeatID(string id) {
	//compare the id with each element in the dishid vector
	for (int i = 0; i < dishid.size(); i++) {
		if (id == dishid[i]) {
			return true;
		}
	}
	return false;
}

double customer::totalFee() {
	string menuid, menuName;	//The id and name of the dish in the menu
	double unitPrice;	//The unit price of the dishes in the menu
	double totalPrice = 0;	//the total fee
	//Calculate the total price 
	//For each dish ordered, find its unit price, multiply it by the quantity and add it to the total price
	for (int i = 0; i < dishid.size(); i++) {
		fstream fin("menu.txt", ios::in);
		while (!fin.eof()) {
			fin >> menuid >> menuName >> unitPrice;
			if (menuid == dishid[i]) {	//Find the location of this dish in the menu
				totalPrice += (unitPrice * dishnum[i]);	//Add to the total price
				fin.close();
				break;
			}
		}
		fin.close();
	}
	return totalPrice;
}

void customer::addOrder() {
	string id;	//User input id
	int num;	//Number of servings entered by the user
	fstream fin("menu.txt", ios::in);	//Input stream of the menu
	string menuid, menuName, menuPrice;	//Store the id, name, and price in the menu
	//Let the user enter the dish id
	cout << "Enter the dish ID you want to add: " << endl;
	getline(cin, id);
	//The following checks if the id exists in the menu
	while (!fin.eof()) {
		fin >> menuid >> menuName >> menuPrice;	//Compare each line of the menu
		if (menuid == id) {	//Matching successful, continue
			break;
		}
		if (fin.eof()) {
			cout << "the dish ID does not exist!" << endl;
			fin.close();
			system("pause");
			return;	//If the user enters an id that does not exist, then the function ends
		}
	}
	//The following checks if the id is duplicated
	if (repeatID(id)) {
		cout << "repeated dish ID!" << endl;
		system("pause");
		fin.close();
		return;	//If the user enters a duplicate id then the function ends
	}
	//Let the user enter the number of the dish
	cout << "Enter the number of the dish: " << endl;
	num = this->enterInt();
	//The user input id is added to the first vector,
	//the name corresponding to the id is added to the second vector, and the number of servings of the dish is added to the third vector.
	dishid.push_back(id);
	dish.push_back(menuName);
	dishnum.push_back(num);
	cout << "Add the dish successfully!" << endl;
	system("pause");
	fin.close();
}

void customer::modOrder() {
	string id, newid;	//The id of the dish the user wants to modify and the new id
	int newnum; //New Quantity
	int n = -1;	//This is the n th dish the user has ordered
	//Collect the id of the dish the user wants to modify
	cout << "Enter the id of the dish you want to modify: " << endl;
	getline(cin, id);
	//Check if the id is among the dishes ordered by the customer
	for (int i = 0; i < dishid.size(); i++) {
		if (dishid[i] == id) {
			n = i;	//record this is the n th dish the user has ordered
		}
	}
	if (n == -1) {	//The customer did not order this dish
		cout << "You haven't ordered this dish yet." << endl;
		system("pause");
		return;	//end
	}
	//Collect new ids and new quantities entered by users
	//Let the user enter the new dish id
	cout << "Enter a new dish ID: " << endl;
	getline(cin, newid);
	fstream fin("menu.txt", ios::in);	//input stream of the menu
	string menuid, menuName, menuPrice;	//Store the id, name, and price in the menu
	//The following checks if the id exists in the menu
	while (!fin.eof()) {
		fin >> menuid >> menuName >> menuPrice;	//Compare each line of the menu
		if (menuid == newid) {	//Matching successful, continue
			break;
		}
		if (fin.eof()) {
			cout << "the dish ID does not exist!" << endl;
			fin.close();
			system("pause");
			return;	//If the user enters an id that does not exist, then the function ends
		}
	}
	//The following checks if the id is duplicated
	if (repeatID(newid) && newid != id) {	//Here is the duplication of ids other than the original id to be considered duplicate
		cout << "repeated dish ID!" << endl;
		system("pause");
		fin.close();
		return;	//If the user enters a duplicate id then the function ends
	}
	//Let the user enter the number of serving
	cout << "Enter the number of the dish: " << endl;
	newnum = this->enterInt();
	//Assign the new three values to the location to be modified
	dishid[n] = newid;
	dish[n] = menuName;
	dishnum[n] = newnum;
	cout << "modify successfully!" << endl;
	system("pause");
	fin.close();
}

void customer::deleteOrder() {
	string id;	//The id of the dish the user wants to delete
	int n = -1;	//This is the n th dish the user has ordered
	//Collect the id of the dish the user wants to delete
	cout << "Enter the id of the dish you want to delete: " << endl;
	getline(cin, id);
	//Check if the id is among the dishes ordered by the customer
	for (int i = 0; i < dishid.size(); i++) {
		if (dishid[i] == id) {
			n = i;	//Record the index of dishes ordered
		}
	}
	if (n == -1) {	//The customer did not order this dish
		cout << "You haven't ordered this dish yet." << endl;
		system("pause");
		return;	//End this method
	}
	//Each element from the n position is moved one place to the front of the vector, and finally the last element is popped, so that it is deleted
	for (int i = n; i < dishid.size() - 1; i++) {
		dishid[i] = dishid[i + 1];
		dish[i] = dish[i + 1];
		dishnum[i] = dishnum[i + 1];
	}
	dishid.pop_back();
	dish.pop_back();
	dishnum.pop_back();
	cout << "delete successfully!" << endl;
	system("pause");
}

void customer::checkout() {
	int userChoice;	//User selection
	cout << "Total price: " << totalFee() << "$" << endl;
	cout << "confirm payment? 1.Yes  2.No" << endl;	//Confirm Payment
	userChoice = this->enterInt();
	if (userChoice == 1) {
		//Print receipt
		cout << "---------------------------receipt-------------------------" << endl;
		cout << "___________________________________________________________" << endl;
		cout << "DishID\t\t\tDishName\t\tDishNumber" << endl;
		cout << "___________________________________________________________" << endl;
		//Show all ordered dishes
		for (int i = 0; i < dishid.size(); i++) {
			cout << dishid[i];
			for (int j = 0; j < 24 - dishid[i].size(); j++)
				cout << " ";
			cout << dish[i];
			for (int j = 0; j < 24 - dish[i].size(); j++)
				cout << " ";
			cout << dishnum[i] << endl;
		}
		//Show total price
		cout << "\nTotal Price: " << totalFee() << endl;
		cout << "-----------------------------------------------------------" << endl;
		system("pause");
	}
	else {
		return;
	}
	//Start writing bills
	fstream fout("order_record.txt", ios::app);	//output stream of the order_record
	fout << username;
	for (int j = 0; j < 48 - username.size(); j++)
		fout << " ";
	fout << totalFee() << endl;
	fout.close();
	//clear the 3 vectors
	dishid.clear();
	dish.clear();
	dishnum.clear();
}

void customer::begin() { // The customer program begins with the customer-related operations.
	int choose;
	bool exit = 0;
	do {
		cout << "\n \n \n" << endl;
		cout << "Please choose an option: " << endl;
		cout << "\n\t1. Order dishes \n\t2. Show the dishes you have ordered \n\t3. Modify what you have already ordered. \n\t4. Delete dish \n\t5. Check out \n\t6. Exit" << endl;
		cout << "\n \n \n" << endl;
		choose = this->enterInt();
		switch (choose)
		{
		case 1:
			addOrder();
			system("cls");
			showInfo();
			showMenu();
			break;
		case 2:
			showOrder();
			system("cls");
			showInfo();
			showMenu();
			break;
		case 3:
			modOrder();
			system("cls");
			showInfo();
			showMenu();
			break;
		case 4:
			deleteOrder();
			system("cls");
			showInfo();
			showMenu();
			break;
		case 5:
			checkout();
			system("cls");
			showInfo();
			showMenu();
			break;
		case 6:
			exit = 1;
			break;
		default:
			cout << "Please choose from the given options" << endl;
			system("cls");
			system("pause");
			break;
		}

	} while (exit != 1);
}