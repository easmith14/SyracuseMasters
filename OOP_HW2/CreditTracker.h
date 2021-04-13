/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
HW #2 - Exercise 4.14 p150
2 / 9 / 21
This dile describes a credit tracker that takes in customer spending information and returns a full credit report.
*/

#include <string>
#pragma once
using std::string;

class CreditTracker
{
public: 
	//initialize with all necessary information to be useful
	CreditTracker(int accountNumber, double startingBalance, double charges, double credits, double creditLimit);
	//synthesize the input information and report the current balance and whether the credit limit has been reached.
	string GetCreditReport();

private:	
	//ensures that account numbers fit requirements
	void setAccountNumber(int accountNumber);
	//returns a formatted string in the format of $xx.xx
	string formatDoubleToCurrency(double inputVal);
	//private info storage to facilitate returning a credit report
	int mAccountNumber;
	double mStartingBalance, mCharges, mCredits, mCreditLimit;
};