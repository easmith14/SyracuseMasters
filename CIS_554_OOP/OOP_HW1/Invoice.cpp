/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
HW #1 - Exercise 3.10 p100
2/1/21
This file implements the Invoice class, which can be used to generate an invoice for a company.
*/

#include "Invoice.h"

Invoice::Invoice(string partNumber, string partDescription,
	int quantity, int pricePerItem)
{
	setPartNumber(partNumber);
	setPartDescription(partDescription);
	setQuantity(quantity);
	setPricePerItem(pricePerItem);
}

string Invoice::getPartNumber()
{
	return _partNumber;
}
void Invoice::setPartNumber(string partNumber)
{
	_partNumber = partNumber;
}

string Invoice::getPartDescription()
{
	return _partDescription;
}
void Invoice::setPartDescription(string partDescription)
{
	_partDescription = partDescription;
}

int Invoice::getQuantity()
{
	return _quantity;
}
void Invoice::setQuantity(int quantity)
{
	//only set quantity if non-negative
	if(quantity < 0)
	{
		_quantity = 0;
	}
	else 
	{
		_quantity = quantity;
	}
}

int Invoice::getPricePerItem()
{
	return _pricePerItem;
}
void Invoice::setPricePerItem(int pricePerItem)
{
	//only set price per item if non-negative
	if (pricePerItem < 0)
	{
		_pricePerItem = 0;
	}
	else
	{
		_pricePerItem = pricePerItem;
	}
}

int Invoice::getInvoiceAmount()
{
	//calculate total price
	return _pricePerItem * _quantity;
}