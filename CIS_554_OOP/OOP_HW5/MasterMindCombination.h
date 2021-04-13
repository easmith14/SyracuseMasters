/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
HW 5 : MasterMind
Last Updated: 3 / 1 / 21
This file describes the base element of the MasterMind game, a combination of guesses and ways to display them.
*/

#pragma once

#include <array>
#include <string>

using std::array;
using std::string;

class MasterMindCombination
{
public:
	//constructor taking in a string to be parsed
	MasterMindCombination(string rawCombination);
	//constructor taking in the formatted combination
	MasterMindCombination(array<int,4> combination);
	//compares the given combination to its own solution, and populates the exact and approximate matches
	void CalculateMatches(MasterMindCombination comparison, int& exactMatches, int& approxMatches);
	//formats the combination to be easier to read
	string CreateFormattedCombinationString();
	//returns the combination
	array<int, 4> GetCombination();

private:
	void setCombination(string rawCombination);
	array<int, 4> mCombination;
};

