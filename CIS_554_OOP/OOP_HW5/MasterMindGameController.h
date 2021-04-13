/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
HW 5 : MasterMind
Last Updated: 3 / 1 / 21
This file describes a controller that runs a game of MasterMind
*/

#pragma once

#include <string>
#include "MasterMindCombination.h"
#include "MasterMindResponse.h"

using std::string;

class MasterMindGameController
{
public:
	//constructor which takes in the total allowed guesses before a loss and generates a random answer to be guessed
	MasterMindGameController(int possibleGuesses);
	//take in a guess from the user, and then populate a response object
	MasterMindResponse ExecuteUserTurn(const MasterMindCombination* guess);
	//formats information about the user's game into a printable format
	string PopulateSummaryString();

private:
	int mPossibleGuesses, mCurrentGuesses;
	MasterMindCombination mSolution;

	//generate a random solution for the game
	MasterMindCombination generateRandomCombination();
};