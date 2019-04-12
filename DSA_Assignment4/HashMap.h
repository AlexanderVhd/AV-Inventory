#include "Item.h"
#include <iostream>
#include <fstream>

using namespace std;

const int SIZE = 100;

class HashMap 
{
	private: 
		Item **inventory;

	public:
		//initialize the inventory table (constructor)
		HashMap()
		{
			inventory = new Item*[SIZE];

			for (int i = 0; i < SIZE; i++) {
				inventory[i] = NULL;
			}
		}

		//desctructor for the inventory table
		~HashMap()
		{
			for (int i = 0; i < SIZE; ++i)
			{
				Item* item = inventory[i];
				while (item != NULL)
				{
					Item * prev = item;
					item = item->next;
					delete prev;
				}
			}
			delete[] inventory;
		}

		int hashFunction(int key);
		void insertItem(int key, string category, string productName, double price);
		void searchByKey(int key);
		void searchByCategory(string category);
		void deleteItem(int key);
		void displayInventory();
		void readFile(string filename);
		void writeToFile(string filename);
};

/*
* Hash function to create the index of the item in the table
*/
int HashMap::hashFunction(int key) {
	return (key % SIZE);
}

/*
* function that inserts item into table (this function is implemented with sorting functionality where the item inserted will always be
* inserted in order within the linked list)	
*/
void HashMap::insertItem(int key, string category, string productName, double price)
{
	int hashIndex = hashFunction(key);
	Item * prev = NULL;
	Item * item = inventory[hashIndex];

	while (item != NULL)
	{
		//sorting condition where we will break if the next product key is larger than the current item's product key
		if (item->productId > key) {
			break;
		}

		//iterate through the linked list in the bucket
		prev = item;
		item = item->next;
	}

	if (item == NULL) {		//executes if we have reached the end of linked list

		//to save memory we create new item by replacing item (we dont need to create new Item)
		item = new Item(key, category, productName, price);

		//executes if we have empty linked list
		if (prev == NULL)
		{
			//insert item in empty linked list
			inventory[hashIndex] = item;
			cout << " Item " << key << " Inserted" << endl;
		}
		else
		{
			//insert item at the end of the linked list
			prev->next = item;
			cout << " Item " << key << " Inserted" << endl;
		}
	}
	else if (item != NULL) {	//executes if we are in between first and last item in linked list

		//create new item (since we need item)
		Item * newItem = new Item(key, category, productName, price);

		//executes if we have just one item in the linked list
		if (prev == NULL)
		{
			//insert newItem before item since item product key is larger
			inventory[hashIndex] = newItem;
			newItem->next = item;
			cout << " Item " << key << " Inserted" << endl;
		}
		else
		{
			//insert newItem between prev and item since item product key is larger
			prev->next = newItem;
			newItem->next = item;
			cout << " Item " << key << " Inserted" << endl;
		}

	}
	else {
		//display error message
		cout << " Entry already exists" << endl;
	}
}

/*
* function that searches for products based on the product key 
*/
void HashMap::searchByKey(int key) 
{
	int hashIndex = hashFunction(key);
	bool condition = false;
	Item * item = inventory[hashIndex];		//go to the bucket which holds the hashIndex

	//iterate through the linked list 
	while (item != NULL) {	

		//print the contents of the node (item) if the nodes product Id equals key
		if (item->productId == key) {	
			cout << endl;
			cout << "    Product ID:     " << item->productId << endl;
			cout << "    Product Name:   " << item->productName << endl;
			cout << "    Category:       " << item->category << endl;
			cout << "    Unit Price:     $" << item->price << endl;
			cout << "    Quantity:       " << item->quantity << endl;
			cout << endl;

			condition = true;
		}

		item = item->next;
	}

	if (!condition) {
		cout << " Item does not Exist" << endl;
	}	
}

/*
* function that searches for products based on the product category
*/
void HashMap::searchByCategory(string category) 
{
	Item * prev = NULL;
	bool condition = false;

	for (int i = 0; i < SIZE; i++) {

		Item * item = inventory[i];

		while (item != NULL) {
			if (item->category == category) {
				cout << endl;
				cout << "    Product ID:     " << item->productId << endl;
				cout << "    Product Name:   " << item->productName << endl;
				cout << "    Category:       " << item->category << endl;
				cout << "	 Unit Price:     $" << item->price << endl;
				cout << "	 Quantity:       " << item->quantity << endl;
				cout << endl;

				condition = true;
			}

			item = item->next;
		}
	}

	if (!condition) {
		cout << " Item not found" << endl;
	}
}

/*
* function to delete an item with specified key
*/
void HashMap::deleteItem(int key)
{
	int hashIndex = hashFunction(key);
	Item * prev = NULL;
	Item * item = inventory[hashIndex];

	while (item != NULL && item->productId != key) {

		//traverse through the linked list
		prev = item;
		item = item->next;
	}

	if (prev != NULL) {
		//connect prev with the item that is connected after the deleted item
		prev->next = item->next;
	}
	else {
		inventory[hashIndex] = NULL;
	}

	//delete value of item and set item to NULL for traversing in later functions
	delete item;


	cout << "    Item " << key << " Deleted" << endl;
}

/*
* function to display the whole inventory
*/
void HashMap::displayInventory() 
{
	Item * prev = NULL;

	//iterate through each bucket in hash table 
	for (int i = 0; i < SIZE; i++) {

		Item * item = inventory[i];

		//iterate through the linked list and print the contents 
		while (item != NULL) {
			cout << endl;
			cout << "    Product ID:     " << item->productId << endl;
			cout << "    Product Name:   " << item->productName << endl;
			cout << "    Category:       " << item->category << endl;
			cout << "    Unit Price:     $" << item->price << endl;
			cout << "    Quantity:       " << item->quantity << endl;
			cout << endl;

			item = item->next;
		}
	}
	
}

/*
* function that reads from the saved file
*/
void HashMap::writeToFile(string filename) 
{
	ofstream myFile;
	Item * prev = NULL;

	//open the file
	myFile.open(filename);

	//check if file opened properly
	if (myFile.is_open()) {
		for (int i = 0; i < SIZE; i++) {

			Item * item = inventory[i];

			//iterate through the hash table and record the contents in file
			while (item != NULL) {
				myFile << endl;
				myFile << "    Product ID:     " << item->productId << endl;
				myFile << "    Product Name:   " << item->productName << endl;
				myFile << "    Category:       " << item->category << endl;
				myFile << "    Unit Price:     $" << item->price << endl;
				myFile << "    Quantity:       " << item->quantity << endl;
				myFile << endl;

				item = item->next;
			}
		}

		//close the file 
		myFile.close();

		cout << "  " << filename << " saved";
	}
	else {
		cout << "  Unable to open file" << endl;
	}
	
}

/*
* function that reads from the file 
*/
void HashMap::readFile(string filename) 
{
	ifstream inventoryFile;
	string line;

	//open the file
	inventoryFile.open(filename);

	//check if file opened properly
	if (inventoryFile.is_open()) {

		//get each line in the file and print them
		while (getline (inventoryFile, line)) {
			cout << line << endl;
		}

		//close the file
		inventoryFile.close();
	}
	else {
		cout << "  Unable to open file" << endl;
	}
}


