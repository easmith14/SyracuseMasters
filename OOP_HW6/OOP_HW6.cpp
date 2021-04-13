/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
HW 6 : SavingsAccount
3/8/21
The main program for testing the SavingsAccount class
*/

#include <iostream>
#include "SavingsAccount.h"
#include "UserPrompter.h"

using std::cout;

int main()
{
	cout << "Welcome to the SavingsAccount testing program!\n\n";

	UserPrompter prompter;

	double accountBalance1 = prompter.promptForDouble("Please enter the starting account balance for the first account: ");
	double accountBalance2 = prompter.promptForDouble("Please enter the starting account balance for the second account: ");
	cout << "\n\n";

	SavingsAccount saver1(accountBalance1), saver2(accountBalance2);

	//get initial interest rate and calculate the first month
	double interestRate = prompter.promptForNonNegativeDouble("First month's interest rate: ");
	
	SavingsAccount::modifyInterestRate(interestRate);

	saver1.calculateMonthlyInterest();
	saver2.calculateMonthlyInterest();

	cout << "Account Balances After One Month:\nAccount 1: " << saver1.getSavingsBalance() 
		<< "\nAccount 2: " << saver2.getSavingsBalance() << "\n\n";


	//get next interest rate and calculate another month
	interestRate = prompter.promptForNonNegativeDouble("Second month's interest rate: ");

	SavingsAccount::modifyInterestRate(interestRate);

	saver1.calculateMonthlyInterest();
	saver2.calculateMonthlyInterest();

	cout << "Account Balances After Two Months:\nAccount 1: " << saver1.getSavingsBalance()
		<< "\nAccount 2: " << saver2.getSavingsBalance() << "\n\n";
}