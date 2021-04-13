/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
HW 5 : MasterMind
Last Updated: 3 / 1 / 21
This file describes the response element of the MasterMind game, a set of information and ways to display it.
*/

#pragma once

#include <string>

using std::string;

class MasterMindResponse
{
public:
	//constructor for a Response object
	MasterMindResponse(int remainingTurns, int exactMatches, int approxMatches);
	//format the response to label the types of matches and seperate them 
	string CreateFormattedResponse();
	//use internal data to decide if the game should end given the state at the time of the response
	bool IsGameOver();

private:
	int mExactMatches, mApproxMatches, mRemainingTurns;
};

