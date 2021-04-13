/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
HW 6 : SavingsAccount
3/8/21
This file describes a SavingsAccount class that tracks the balance of an account and its interest over time.
*/

#include "SavingsAccount.h"

//declare the annual interest rate to be 0 initially
double SavingsAccount::annualInterestRate = 0;

//constructor to create a SavingsAccount and sets the starting balance to the input value
SavingsAccount::SavingsAccount(double initialBalance)
: savingsBalance(initialBalance)
{
}

//change the static interest rate to the given new rate
void SavingsAccount::modifyInterestRate(double interestRate)
{
	annualInterestRate = interestRate;
}

//calculate the monthly interest on the current balance and calculate the updated balance
//note that the monthly interest is the annual interest over 12 months
void SavingsAccount::calculateMonthlyInterest()
{
	savingsBalance += savingsBalance * (annualInterestRate / 12.0);
}

//return the current savings balance, formatted to dollars, enforcing exactly 2 decimal places
string SavingsAccount::getSavingsBalance()
{
	double roundedDouble = ceil(savingsBalance * pow(10, 2)) / pow(10, 2);
	char test[50];
	sprintf_s(test, "%0.2f", roundedDouble);
	return "$" + (string)test;
}
