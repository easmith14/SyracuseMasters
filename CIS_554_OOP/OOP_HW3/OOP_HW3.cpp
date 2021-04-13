/*
Evan Smith
CIS 554-M401 Object Oriented Programming in C++
Syracuse University
HW #3 - Exercise 5.16 p206
2/15/21
This program takes in numeric values from the user and prints corresponding bar charts
*/

#include <iostream>
#include <string>
#include <vector>
#include "UserPrompter.h"

using std::cout;
using std::string;
using std::vector;
using std::to_string;

static int NUM_INPUTS = 5;

int main()
{
	vector<int> inputs;
	UserPrompter prompter;

	cout << "Welcome to the super fancy bar graph program!\nEnter " + to_string(NUM_INPUTS) + " values to graph!\n\n";

	//read in some number of inputs into a vector
	for (int i = 1; i <= NUM_INPUTS; i++)
	{
		int inputValue = prompter.promptForNonNegativeInt("Enter bar graph value #" + to_string(i) + ": ");
		inputs.push_back(inputValue);
	}


	//for each value in the vector, output the bar graph
	for (int input : inputs)
	{
		string barGraph = "";

		//add as many asterixs as the value
		for (int i = 0; i < input; i++)
		{
			barGraph += "*";
		}
		
		cout << barGraph << "\n";
	}
}