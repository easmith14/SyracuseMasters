/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
HW 5 : MasterMind
Last Updated: 3 / 1 / 21
This file implements the base element of the MasterMind game, a combination of guesses and ways to display them.
*/

#include "MasterMindCombination.h"

using std::to_string;

//constructor taking in a string to be parsed
MasterMindCombination::MasterMindCombination(string rawCombination)
{
	setCombination(rawCombination);
}

//constructor taking in a pre-parsed combination for direct assignment
MasterMindCombination::MasterMindCombination(array<int, 4> combination)
	: mCombination(combination)
{
}

//compares the given combination to its own solution, and populates the exact and approximate matches
//exact matches have same value in the same index. Approx matches are non-exact match indices whose values are in a different location
void MasterMindCombination::CalculateMatches(MasterMindCombination comparison, int& exactMatches, int& approxMatches)
{
	exactMatches = 0;
	approxMatches = 0;
	array<bool, 4> comparisonLocationUsed{ false, false, false, false };
	array<bool, 4> combinationLocationUsed{ false, false, false, false };


	array<int, 4> comparisonCombination = comparison.GetCombination();

	//first, check for all exact matches
	for (size_t i = 0; i < comparisonCombination.size(); i++)
	{
		//log all exact matches and their location in the combinations
		if (comparisonCombination.at(i) == mCombination.at(i))
		{
			exactMatches++;
			comparisonLocationUsed.at(i) = true;
			combinationLocationUsed.at(i) = true;
		}
	}

	//then, check one by one for approx matches, ignoring positions already used
	for (size_t i = 0; i < comparisonCombination.size(); i++)
	{
		for (size_t j = 0; j < mCombination.size(); j++)
		{
			if (!comparisonLocationUsed.at(i) && !combinationLocationUsed.at(j) && comparisonCombination.at(i) == mCombination.at(j))
			{
				approxMatches++;
				comparisonLocationUsed.at(i) = true;
				combinationLocationUsed.at(j) = true;
			}
		}
	}
}

//formats the internal combination to be easier for the player to read in game
string MasterMindCombination::CreateFormattedCombinationString()
{
	string formattedCombination = "";

	for (int peg : mCombination)
	{
		formattedCombination += to_string(peg) + " ";
	}

	return formattedCombination;
}

//return the internal combination
array<int, 4> MasterMindCombination::GetCombination()
{
	return mCombination;
}

//set the combination, trimming excess if input too long and filling gaps with default pegs if input too short
void MasterMindCombination::setCombination(string rawCombination)
{
	for (size_t i = 0; i < 4; i++)
	{
		//if not enough pegs guessed by the user, default to 1
		if (i >= rawCombination.size())
		{
			mCombination.at(i) = 1;
		}
		else
		{
			mCombination.at(i) = std::stoi(rawCombination.substr(i, 1));
		}
	}
}
