/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
HW #1 - Exercise 3.10 p100
2/1/21
This header describes a class that can be used to generate an invoice for a company.
*/

#include <string>
using std::string;

class Invoice 
{
private:
	string _partNumber;
	string _partDescription;
	int _quantity;
	int _pricePerItem;

public:
	Invoice(string partNumber, string partDescription,
		int quantity, int pricePerItem);

	string getPartNumber();
	void setPartNumber(string partNumber);

	string getPartDescription();
	void setPartDescription(string partDescription);

	int getQuantity();
	void setQuantity(int quantity);

	int getPricePerItem();
	void setPricePerItem(int pricePerItem);

	int getInvoiceAmount();
};