/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
HW #1 - Exercise 3.10 p100
2/1/21
This program provides an example usage of the Invoice class and prints its data values and function results
*/

#include <iostream>
#include <vector>
#include "Invoice.h"
using std::string;
using std::cout;
using std::vector;

int main() 
{
	//create a new set of invoices for testing, including examples with negative quantities and prices
	vector<Invoice> invoices;
	invoices.push_back(Invoice("1212T12", "A metal ruler with engraved markings", 5, 2));
	invoices.push_back(Invoice("3434S34", "A set of screws", -5, 8));
	invoices.push_back(Invoice("5656R56", "Spray paint", 4, -1));

	//print all information from the invoices
	int invoiceCount = invoices.size();
	for (Invoice invoice : invoices)
	{
		cout << "---------------------------------------------------------------\n";
		cout << "Invoice #" << invoiceCount-- << " information:" << endl;
		cout << "Part Number: " << invoice.getPartNumber() << endl;
		cout << "Part Description: " << invoice.getPartDescription() << endl;
		cout << "Quantity: " << invoice.getQuantity() << endl;
		cout << "Price/Item: " << invoice.getPricePerItem() << endl;
		cout << "Invoice Amount: " << invoice.getInvoiceAmount() << endl;
		cout << "---------------------------------------------------------------\n\n"
	}

}