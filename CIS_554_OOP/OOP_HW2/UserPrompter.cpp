/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
General Library
2 / 9 / 21
This file implements a series of functions to facilitate safe prompting of users and parsing of their responses.
*/

#include <iostream>
#include "UserPrompter.h"
using std::cout;
using std::cin;

//prompt the user using the provided string, then verify that it can be cast to an int.
//If bad input provided, reprompt until it's correct
int UserPrompter::promptForInt(string prompt)
{
    bool success = false;
    string userInput = "";
    int parsedInt;

    while (!success)
    {
        cout << prompt;
        cin >> userInput;
        try
        {
            parsedInt = std::stoi(userInput);
            success = true;
        }
        catch (std::exception e)
        {
            cout << "Please enter an integer!\n";
        }
    }

    return parsedInt;
}

//prompt the user using the provided string, then verify that it can be cast to a double.
//If bad input provided, reprompt until it's correct
double UserPrompter::promptForDouble(string prompt)
{
    bool success = false;
    string userInput = "";
    double parsedDouble;

    while (!success)
    {
        cout << prompt;
        cin >> userInput;
        try
        {
            parsedDouble = std::stod(userInput);
            success = true;
        }
        catch (std::exception e)
        {
            cout << "Please enter a double!\n";
        }
    }

    return parsedDouble;
}