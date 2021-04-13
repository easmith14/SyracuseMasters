/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
HW #2 - Exercise 4.14 p150
2 / 9 / 21
This file implements a credit tracker that takes in customer spending information and returns a full credit report.
*/

#include "CreditTracker.h"
#include <cmath>
using std::to_string;
using std::ceil;

//create a CreditTracker, taking all dollar values no matter what, as we do not have value limits. Validate Account Numbers.
CreditTracker::CreditTracker(int accountNumber, double startingBalance, double charges, double credits, double creditLimit)
: mStartingBalance(startingBalance), mCharges(charges), mCredits(credits), mCreditLimit(creditLimit)
{
	setAccountNumber(accountNumber);
}

//Only accept account numbers >= 0. Default to 0.
void CreditTracker::setAccountNumber(int accountNumber)
{
	if (accountNumber < 0)
	{
		mAccountNumber = 0;
	}
	else
	{
		mAccountNumber = accountNumber;
	}
}

//take in a double and round it to the cents, then format to remove trailing zeros
string CreditTracker::formatDoubleToCurrency(double inputVal)
{
	double roundedDouble = ceil(inputVal * pow(10, 2)) / pow(10, 2);
	char test[50];
	sprintf_s(test, "%0.2f", roundedDouble);
	return "$" + (string)test;
}

//return a formatted string with the information about this clients credit. Report back if credit limit has been exceeded.
string CreditTracker::GetCreditReport()
{
	double newBalance = mStartingBalance + mCharges - mCredits;
	string newBalanceFormatted = formatDoubleToCurrency(newBalance);
	string creditReport = "";
	creditReport += "New Balance is : " + newBalanceFormatted + "\n";
	
	//catch if limit has been exceeded and log important information
	if (newBalance > mCreditLimit)
	{
		creditReport += "Account		: " + to_string(mAccountNumber) + "\n";
		creditReport += "Credit limit	: " + formatDoubleToCurrency(mCreditLimit) + "\n";
		creditReport += "Balance		: " + newBalanceFormatted + "\n";
		creditReport += "Credit Limit Exceeded.\n";
	}

	return creditReport;
}

