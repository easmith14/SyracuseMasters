/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
HW 5 : MasterMind
Last Updated: 3 / 1 / 21
This file implements a controller that runs a game of MasterMind
*/

#include <ctime>
#include "MasterMindGameController.h"

using std::to_string;

//constructor which takes in the total allowed guesses before a loss and generates a random answer to be guessed
MasterMindGameController::MasterMindGameController(int possibleGuesses)
	: mPossibleGuesses(possibleGuesses), mCurrentGuesses(0), mSolution(generateRandomCombination())
{
}

//takes in a guess from the user, and then populates a response object
MasterMindResponse MasterMindGameController::ExecuteUserTurn(const MasterMindCombination* guess)
{
	mCurrentGuesses++;

	int exactMatches, approxMatches;
	mSolution.CalculateMatches(*guess, exactMatches, approxMatches);

	return MasterMindResponse(mPossibleGuesses - mCurrentGuesses, exactMatches, approxMatches);
}

//formats internal data depending on whether the player won or lost
string MasterMindGameController::PopulateSummaryString()
{
	//if the game ended as a loss for the player
	if (mPossibleGuesses == mCurrentGuesses)
	{
		return "\nGame Over! You did not guess the combination in " + to_string(mPossibleGuesses) + " turns.\nThe correct combination was: " + mSolution.CreateFormattedCombinationString() + "\n\n";
	}
	//if the game ended as a win for the player
	else
	{
		return "\nCongratulations! You guessed the combination in " + to_string(mCurrentGuesses) + " turns with " + to_string(mPossibleGuesses - mCurrentGuesses) + " to spare.\n\n";
	}
}

//creates a random set of values and uses them to create a combination for this game instance
MasterMindCombination MasterMindGameController::generateRandomCombination()
{
	array<int, 4> combination;

	srand(time(NULL));
	for (int i = 0; i < 4; i++)
	{
		combination.at(i) = (rand() % 6) + 1;
	}

	return MasterMindCombination(combination);
}
