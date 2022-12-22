#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

auto path = "inventory_item_data.txt"; // name of file

struct inventoryItem {
	string name;
	string itemID;
	string category;
	int itemCount;
	string allocatedTo[10]; // An array where we will store the users who have borrowed items
	bool active = true;
};


void addItem(struct inventoryItem*, int*);
void showItem(struct inventoryItem*);
void searchItem(struct inventoryItem*);
void editItem(struct inventoryItem*);
void deleteItem(struct inventoryItem*);
void assignItem(struct inventoryItem*);
void retrieveItem(struct inventoryItem*);
void viewMembers(struct inventoryItem*);

// Reading & Writing File
void readItem(ifstream&, inventoryItem*, int&);
void writeItem(inventoryItem*);


int main() {
	const int size = 10; // Number of ITEMS that can be stored in the array
	inventoryItem arr[size]; 
	int i = 0;

	{
		ofstream file(path, ios::app); // Creates a file if it does not already exists
		file.close();
	}

	ifstream file(path, std::ios::in); // Opening file to read data from it

	if (file)
		readItem(file, arr, i); // Calling function to read data

	file.close();


	char option = 0;


	cout << setw(80) << "--------Welcome to Inventory management system--------" << endl;

	do
	{
		cout << endl << "Please choose an option from below to continue" << endl;
		cout << "1. Add inventory items" << endl
			<< "2. View all inventory items" << endl
			<< "3. Search inventory item" << endl
			<< "4. Edit inventory item " << endl
			<< "5. Delete inventory item" << endl
			<< "6. Assign inventory item" << endl
			<< "7. Retrieve inventory item" << endl
			<< "8. View members" << endl
			<< "9. Exit" << endl;

		cin >> option;
		cin.ignore(1000, '\n');

		// Choice of options available on menu
		if (option == '1') {
			addItem(arr, &i);
		}
		else if (option == '2') {
			showItem(arr);
		}
		else if (option == '3') {
			searchItem(arr);
		}
		else if (option == '4') {
			editItem(arr);
		}
		else if (option == '5') {
			deleteItem(arr);
		}
		else if (option == '6') {
			assignItem(arr);
		}
		else if (option == '7') {
			retrieveItem(arr);
		}
		else if (option == '8') {
			viewMembers(arr);
		}
		else if (option == '9') {
			return 0;
		}
		else
			cout << ":/ Invalid Command" << endl;

		writeItem(arr); // Writes the record in file as soon as a function ends

	} while (option != '9');

	return 0;

}

// Function to add item details to array
void addItem(struct inventoryItem* intArr, int* count) {
	cout << "Please enter details of inventory item: " << endl;

	string id;

	do { // Do while loops to make sure that user must enter data of item
		cout << "Name: " << endl;
		getline(cin, intArr[*count].name);
	} while (intArr[*count].name.empty()); 

	do
	{
		cout << "Number of items: " << endl;
		cin >> intArr[*count].itemCount;
		cin.ignore(1000, '\n');

		if (intArr[*count].itemCount < 1) {
			cout << ":/ Error -> Please add at least 1 item " << endl;
		}

	} while (intArr[*count].itemCount < 1);

	int flag = 1;
	// Taking unique ID for each Item
	do {

		flag = 1;

		cout << "ID: " << endl;
		getline(cin, id);

		for (int i = 0; !intArr[i].itemID.empty(); i++) {
			if (id == intArr[i].itemID) {
				flag = 0;
				break;
			}
		}

		if (flag == 0) {
			cout << "This ID already exists :/ Please choose another one" << endl;
		}

	} while (flag == 0 || id.empty());

	if (flag == 1) {
		intArr[*count].itemID = id;
	}

	do {
		cout << "Category: " << endl;
		getline(cin, intArr[*count].category);
	} while (intArr[*count].category.empty());

	(*count)++; // Incrementing count by 1, so next item details are assigned to next index

}

// Function to display All Items
void showItem(struct inventoryItem* intArr) {

	int j = 0;
	while (!intArr[j].name.empty())
	{
		if (intArr[j].active != false) // If an item is not deleted
		{
			cout << "Name: " << intArr[j].name << endl;
			cout << "Item Count: " << intArr[j].itemCount << endl;
			cout << "ID: " << intArr[j].itemID << endl;
			cout << "Category: " << intArr[j].category << endl;

			cout << "----------------------------------------------"
				<< endl;
		}

		j++;
	}

}

// Function to search Item
void searchItem(struct inventoryItem* arr) {

	string itemID;
	int j = 0, index = 0, flag = 0;

	cout << "Enter Item ID: " << endl;
	cin >> itemID;

	while (!arr[j].name.empty()) // Loop runs as long as there is an item
	{
		if (itemID == arr[j].itemID) { // If item is found, its index is stored
			index = j;
			flag = 1;
		}

		j++;
	}

	if (flag == 1)
	{
		cout << "Searched item details: " << endl << "------------------------------" << endl
			<< "Name: " << arr[index].name << endl
			<< "Item Count: " << arr[index].itemCount << endl
			<< "ID: " << arr[index].itemID << endl
			<< "Category: " << arr[index].category << endl
			<< "------------------------------";

	}
	else
		cout << itemID << " Not Found :/" << endl;

}

// Function to edit item
void editItem(struct inventoryItem* arr) {

	string itemID;
	int j = 0, index = 0, flag = 0;

	cout << "Enter Item ID to edit: " << endl;
	cin >> itemID;
	cin.ignore(1000, '\n');

	while (!arr[j].name.empty()) {
		if (itemID == arr[j].itemID) {
			index = j;
			flag = 1;
		}

		j++;
	}

	if (flag == 1)
	{
		cout << "Name: " << endl;
		getline(cin, arr[index].name);

		do
		{
			cout << "Number of items: " << endl;
			cin >> arr[index].itemCount;
			cin.ignore(1000, '\n');

			if (arr[index].itemCount < 1) {
				cout << ":/ Error -> Please add at least 1 item " << endl;
			}

		} while (arr[index].itemCount < 1);

		cout << "Category: " << endl;
		getline(cin, arr[index].category);
	}
	else
		cout << itemID << " Not Found :/" << endl;

}

// Function to delete an item
void deleteItem(struct inventoryItem* arr) {

	string itemID;
	int j = 0, index = 0, flag = 0;

	cout << "Enter Item ID to delete: " << endl;
	cin >> itemID;

	while (!arr[j].name.empty()) {
		if (itemID == arr[j].itemID) {
			index = j;
			flag = 1;
		}


		j++;
	}

	if (flag == 1)
	{
		arr[index].active = false; // Changes the active attribute of array index to false, so we consider it deleted

	}
	else
		cout << itemID << " Not Found :/" << endl;

}

// Function to borrow items from system
void assignItem(struct inventoryItem* arr) {

	string name, itemID;
	int index = 0, j = 0, a = 0, flag = 0, flag2 = 0, temIndex = 0;

	cout << "Enter item ID you want to Assign: " << endl;
	cin >> itemID;

	while (!arr[j].name.empty()) {
		if (itemID == arr[j].itemID) {
			index = j;
			flag = 1;
		}


		j++;
	}

	if (flag == 1)
	{
		// for a unique username
		do {

			flag2 = 1;

			cout << "Please enter username: " << endl;
			cin >> name;

			for (int i = 0; !arr[index].allocatedTo[i].empty(); i++) {
				if (name == arr[index].allocatedTo[i]) {
					flag2 = 0;
					break;
				}
			}

			if (flag2 == 0) {
				cout << "This username already exists :/ Please choose another one" << endl;
			}

		} while (flag2 == 0);

		auto& itemCount = arr[index].itemCount;

		// If the index is empty, adds the name of the user at that index other wise increment to the next index and store it there
		while (true)
		{
			auto& slot = arr[index].allocatedTo[a++];

			if (slot.empty() && flag2 == 1)
			{
				slot.assign(name);
				break;
			}
		}


		--itemCount; // decrementing item count by 1
	}
	else
		cout << itemID << " Not Found :/" << endl;
}

// Functing for retriving an Item from user
void retrieveItem(struct inventoryItem* arr) {
	string itemID, userName;
	int j = 0, index = 0, flag = 0;

	cout << "Enter Item ID to return: " << endl;
	cin >> itemID;

	while (!arr[j].name.empty()) {
		if (itemID == arr[j].itemID) {
			index = j;
			flag = 1;
		}


		j++;
	}

	if (flag == 1)
	{

		cout << "Please enter your name: " << endl;
		cin >> userName;

		int n = 0;

		bool found = false;

		for (n = 0; n < 10; n++) {
			if (userName == arr[index].allocatedTo[n]) // Checks if the given name is in allocatedTo array of given item (List of Borrowers)
			{
				auto& slot = arr[index];
				auto& alt = slot.allocatedTo;

				++slot.itemCount; // Increments the item count by 1

				for (int i = n; i < 10 - 1; i++) { // replaces the retrived username with next username
					alt[i] = alt[i + 1];
				}

				alt[10 - 1] = ""; // Makes the last input empty

				found = true;
				break;
			}
		}

		if (!found)
			cout << "Sorry! This user is not in our Borrower's List" << endl;
	}
	else
		cout << itemID << " Not Found :/" << endl;
}

// Function to display borrowers
void viewMembers(struct inventoryItem* arr) {

	string itemID;
	int j = 0, m = 0, index = 0, flag = 0;

	cout << "Enter Item ID to check Borrowers: " << endl;
	cin >> itemID;

	while (!arr[j].name.empty()) {
		if (itemID == arr[j].itemID) {
			index = j;
			flag = 1;
		}


		j++;
	}

	if (flag == 1)
	{
		while (!arr[index].allocatedTo[m].empty()) { // Till there is a borrower in an array
			cout << arr[index].allocatedTo[m] << endl;
			m++;
		}

		if (arr[index].allocatedTo[0].empty()) { // If there is no borrower
			cout << ":/ No one has borrowed " << itemID << " yet" << endl;
		}

	}
	else
		cout << itemID << " Not Found :/" << endl;

}

// File Handling

// Reading data from file
void readItem(ifstream& fin, struct inventoryItem* arr, int& count) {
	int j = 0;

	while (!fin.eof()) {
		getline(fin, arr[j].itemID);
		if (fin.eof() || arr[j].itemID.empty()) // If file has opened for the first time, not to read records from it
			break;
		getline(fin, arr[j].name);
		getline(fin, arr[j].category);
		fin >> arr[j].itemCount;
		fin.ignore(1000, '\n');

		for (int a = 0; a < 10; ++a) // To read list of borrowers
		{
			getline(fin, arr[j].allocatedTo[a]);
		}

		j++;
		count++;
	}

}

// Function to write in the file
void writeItem(inventoryItem* arr) {

	ofstream fout(path); // Opens file to write each time

	int j = 0;

	while (!arr[j].name.empty()) { // Till there is an item, keep writing
		if (arr[j].active != false)
		{
			fout << arr[j].itemID << endl;
			fout << arr[j].name << endl;
			fout << arr[j].category << endl;
			fout << arr[j].itemCount << endl;

			for (int a = 0; a < 10; ++a)
			{
				fout << arr[j].allocatedTo[a] << endl;
			}
		}

		j++;
	}

}