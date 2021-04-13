/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
HW 5 : MasterMind
Last Updated: 3 / 1 / 21
This file implements the response element of the MasterMind game, a set of information and ways to display it.
*/

#include "MasterMindResponse.h"

using std::to_string;

//constructor for a Response object
MasterMindResponse::MasterMindResponse(int remainingTurns, int exactMatches, int approxMatches)
:mRemainingTurns(remainingTurns), mExactMatches(exactMatches), mApproxMatches(approxMatches)
{
}

//format the response to label the types of matches and seperate them visually
string MasterMindResponse::CreateFormattedResponse()
{
	return "| Exact: " + to_string(mExactMatches) + " | Approx: " + to_string(mApproxMatches) + " |\n";
}

//use internal data to decide if the game should end given the state at the time of the response
//this is true when either the user ran out of turns or guessed the code completely
bool MasterMindResponse::IsGameOver()
{
	return mRemainingTurns <=0 || mExactMatches == 4;
}
