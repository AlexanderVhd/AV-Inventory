// DSA_Assignment4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HashMap.h"
#include <cctype>

void displayError() {

	//repair the stream and clear the buffer (set the maximum number of characters to ignore)
	cin.clear();
	cin.ignore(std::numeric_limits<int>::max(), '\n');

	//display error message
	cout << "\nError: Please Enter Valid Input\n" << endl;
}

int main()
{
	int option, productId, delProductId, userCategory, searchType, loadOption, fileOption;
	string productCategory, productName, writeFileName, loadFileName;
	double productPrice;
	bool condition;
	HashMap inventory;

	cout << "====================" << endl;
	cout << "  Inventory System  " << endl;
	cout << "====================" << endl;

	//exit option
	bool exit = false;
	
	while (!exit) {
		cout << endl;
		cout << "(1) Insert Product" << endl;
		cout << "(2) Search for Product" << endl;
		cout << "(3) Display Inventory" << endl;
		cout << "(4) Delete Product" << endl;
		cout << "(5) Quit" << endl;
		cout << "\nEnter your choice : " << endl;
		cin >> option;

		//validate if user entered integer
		if (cin.fail()) {
			displayError();
			continue;
		}

		switch (option)
		{
		case 1:

			cout << " Insert Product" << endl;
			cout << " --------------------------------------------------------" << endl;

			do {
				cout << endl;
				cout << "    Enter the product ID (must be greater than 100): ";
				cin >> productId;

				//check user input, set condition to true and loop back if user input is invalid
				if (!(productId > 100) || isdigit(productId)) {

					//change the condition to false and clear the error flags in cin
					condition = true;

					//display error message and start loop from beginning
					displayError();
					continue;
				}
				else {
					//if there are no errors in user input, then set condition to false to break from loop 
					condition = false;
				}

				//display options for item category 
				cout << endl;
				cout << "    Select the category of the product\n\n";
				cout << "      (1) Raw Materials\n";
				cout << "      (2) Work In Progress\n";
				cout << "      (3) Finished Goods\n";
				cout << "      (4) MRO Supplies\n\n";
				cin >> userCategory;

				//check user input, set condition to true and loop back if user input is invalid
				if (userCategory < 1 || userCategory > 4 || isdigit(userCategory)) {
					
					//change the condition to false and clear the error flags in cin
					condition = true;

					//display error message and start loop from beginning
					displayError();
					continue;
				}
				else {
					productCategory = (userCategory == 1) ? "Raw Materials"
						: (userCategory == 2) ? "Work In Progress"
						: (userCategory == 3) ? "Finished Goods"
						: "MRO Supplies";

					condition = false;
				}

				cout << "    Enter the name of the product: ";
				cin >> productName;
				cout << endl;

				cout << "    Enter the unit price of the product: ";
				cin >> productPrice;
				cout << endl;

			} while (condition);

			//call the insert item function to insert item into inventory table
			inventory.insertItem(productId, productCategory, productName, productPrice);

			cout << " --------------------------------------------------------" << endl;
			break;
			
		case 2:

			cout << " Search Product" << endl;
			cout << " --------------------------------------------------------" << endl;

			do {

				//display options for searching inventory
				cout << endl;
				cout << "    Select a search option \n\n";
				cout << "      (1) Search by Key\n";
				cout << "      (2) Search by Category\n";
				cout << "      (3) Back\n";
				cin >> searchType;

				//handle each user option 
				if (searchType == 1) {
					cout << "\n        Enter Product ID: " << endl;
					cin >> productId;

					//call the search by key function to search the hash map for the product Id
					inventory.searchByKey(productId);

					//set condition to false to break out of loop since user input is validated
					condition = false;
				}
				else if (searchType == 2) {
					cout << "    Select the category\n\n"; 
					cout << "      (1) Raw Materials\n";
					cout << "      (2) Work In Progress\n";
					cout << "      (3) Finished Goods\n";
					cout << "      (4) MRO Supplies\n\n";
					cin >> userCategory;

					//check user input, set condition to true and loop back if user input is invalid
					if (userCategory < 1 || userCategory > 4) {
						displayError();
						condition = true;
					}
					else {
						//use conditionals to assign item category
						productCategory = (userCategory == 1) ? "Raw Materials"
							: (userCategory == 2) ? "Work In Progress"
							: (userCategory == 3) ? "Finished Goods"
							: "MRO Supplies";

						//call the search by category function from the hash map and set condition to false to break out of loop
						inventory.searchByCategory(productCategory);
						condition = false;
					}
				}
				else if(searchType == 3) {

					//make the condition false to go back to the original options
					condition = false;
					break;
				}
				else {
					//display error message and start loop from beginning
					displayError();
					condition = true;
				}
			} while (condition);

			cout << " --------------------------------------------------------" << endl;
			break;

		case 3:

			do {
				cout << endl;
				cout << "(1) Retrieve Inventory" << endl;
				cout << "(2) Load Inventory from File " << endl;
				cin >> loadOption;

				if (loadOption == 1) {
					cout << " Retrieve Inventory" << endl;
					cout << " --------------------------------------------------------" << endl;

					//display local inventory 
					inventory.displayInventory();

					//display options for saving to a file
					cout << endl;
					cout << "  (1) Save				(2) Cancel" << endl;
					cin >> fileOption;

					if (fileOption == 1) {
						cout << "  Enter File Name (add .txt): " << endl;
						cin >> writeFileName;

						//call function to write all inventory to the file
						inventory.writeToFile(writeFileName);

					}

					//set condition to false to break out of loop since user input is validated
					condition = false;

					cout << endl;
					cout << " --------------------------------------------------------" << endl;
				}
				else if (loadOption == 2) {
					cout << " Load Inventory from file" << endl;
					cout << " --------------------------------------------------------" << endl;

					cout << "  Enter File Name (.txt): " << endl;
					cin >> loadFileName;

					//call function to read file with given filename
					inventory.readFile(loadFileName);

					//set condition to false to break out of loop since user input is validated
					condition = false;

					cout << endl;
					cout << " --------------------------------------------------------" << endl;
				}
				else {
					displayError();
					condition = true;
				}
			} while (condition);
			
			break;

		case 4:

			//condition variable for user input validation
			condition = false;

			cout << endl;
			cout << " Delete Product" << endl;
			cout << " --------------------------------------------------------" << endl;

			do {
				cout << endl;
				cout << "    Enter the product ID (must be greater than 100): ";
				cin >> delProductId;

				//check user input, set condition to true and loop back if user input is invalid
				if (productId <= 100) {
					condition = true;

					displayError();
					continue;
				}
				else {
					condition = false;
				}

			} while (condition);

			//call the delete by key function to delete the item
			inventory.deleteItem(delProductId);

			cout << " --------------------------------------------------------" << endl;

		case 5:
			exit = true;

			cout << "=====================" << endl;
			cout << "  Exiting Inventory  " << endl;
			cout << "=====================" << endl;

			break;

		default:
			cout << "Invalid choice\n";
		}

	}

	return 0;

}

