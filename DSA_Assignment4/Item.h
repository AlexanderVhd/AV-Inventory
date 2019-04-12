
#ifndef ITEM_H
#define ITEM_H

#include <string>

using std::string;

class Item 
{

public:
	int productId;
	string category;
	string productName;
	int quantity; 
	double price;

	Item *next;

	Item(int key, string category, string productName, double price) 
	{
		this->productId = key;
		this->category = category;
		this->productName = productName;
		this->price = price;
		this->quantity = 1;
		this->next = NULL;
	}
};


#endif /* ITEM_H */