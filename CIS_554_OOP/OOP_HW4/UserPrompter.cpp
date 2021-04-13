/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
General Library
Last Updated: 2 / 22 / 21
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

//an extension of prompForInt which enforces that the response is non-negative
//If bad input provided, reprompt until it's correct
int UserPrompter::promptForPositiveInt(string prompt)
{
    bool success = false;
    int parsedInt = -1;

    while (!success)
    {
        parsedInt = promptForInt(prompt);

        if (parsedInt <= 0)
        {
            cout << "Please enter a positive integer!\n";
        }
        else
        {
            success = true;
        }
    }

    return parsedInt;
}

//an extension of prompForInt which enforces that the response is non-negative
//If bad input provided, reprompt until it's correct
int UserPrompter::promptForNonNegativeInt(string prompt)
{
    bool success = false;
    int parsedInt = -1;

    while (!success)
    {
        parsedInt = promptForInt(prompt);

        if (parsedInt < 0)
        {
            cout << "Please enter a non-negative integer!\n";
        }
        else
        {
            success = true;
        }
    }
    
    return parsedInt;
}

//an extension of prompForInt which enforces that the response is non-negative OR is a given sentinal value
//If bad input provided, reprompt until it's correct
int UserPrompter::promptForNonNegativeIntOrSentinal(string prompt, int sentinal)
{
    bool success = false;
    int parsedInt = -1;

    while (!success)
    {
        parsedInt = promptForInt(prompt);

        if (parsedInt < 0 && parsedInt != sentinal)
        {
            cout << "Please enter a non-negative integer or " << sentinal << "!\n";
        }
        else
        {
            success = true;
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