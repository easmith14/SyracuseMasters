/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
HW #2 - Exercise 4.14 p150
2 / 9 / 21
This program takes input required to populate a credit tracker, and then displays the resulting credit report.
It can then generate as many other credit reports as desired.
*/

#include <iostream>
#include "CreditTracker.h"
#include "UserPrompter.h"
using std::cout;
using std::cin;

int main()
{
    int accountNumber = 0;
    double startingBalance, totalCharges, totalCredits, creditLimit;
    UserPrompter prompter;

    cout << "Welcome to the credit tracking system. Please enter the first account information to begin.\n";

    //gather account information for as many customers as desired
    while (true)
    {
        //check account number for exit sentinal
        accountNumber = prompter.promptForInt("\nEnter account number (or -1 to exit): ");
        if (accountNumber == -1) break;

        //gather all other values, with type checking in the prompt function
        startingBalance = prompter.promptForDouble("Enter starting balance: ");
        totalCharges = prompter.promptForDouble("Enter total charges: ");
        totalCredits = prompter.promptForDouble("Enter total credits: ");
        creditLimit = prompter.promptForDouble("Enter credit limit: ");

        //create credit tracker, then generate and display credit report
        CreditTracker creditTracker(accountNumber, startingBalance, totalCharges, totalCredits, creditLimit);
        cout << creditTracker.GetCreditReport();
    }
}
