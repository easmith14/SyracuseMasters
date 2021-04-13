/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
General Library
2 / 9 / 21
This file describes a series of functions to facilitate safe prompting of users and parsing of their responses.
*/

#pragma once
#include <string>
using std::string;
class UserPrompter
{
public:
	//prints provided prompt and returns parsed int, or reprompts.
	int promptForInt(string prompt);
	//prints provided prompt and returns parsed double, or reprompts.
	double promptForDouble(string prompt);
};

