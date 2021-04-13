/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
HW 6 : SavingsAccount
3/8/21
This file implements a SavingsAccount class that tracks the balance of an account and its interest over time.
*/

#pragma once
#include <string>

using std::string;

class SavingsAccount
{
public:
	//constructor to create a SavingsAccount given a starting balance
	SavingsAccount(double initialBalance);
	//change the static interest rate to the given new rate
	static void modifyInterestRate(double interestRate);
	//calculate the monthly interest on the current balance and calculate the updated balance
	void calculateMonthlyInterest();
	//return the current savings balance, formatted to dollars
	string getSavingsBalance();
private:
	static double annualInterestRate;
	double savingsBalance;
};

