/*
Evan Smith
CIS 554-M401 Object Oriented Programming in C++
Syracuse University
HW #4 - Exercise 6.57-61 p281
2/22/21
This program describes a trainer which creates math questions based on input parameters,
and tracks student's progress in their answers
*/

#pragma once

#include <vector>
#include <string>
#include "MathQuestion.h"
#include "ProblemType.h"

using std::vector;
using std::string;

class ArithmeticTrainer
{
public:
	//construct an ArithmeticTrainer
	ArithmeticTrainer(int problemType, int difficulty,
		vector<string> correctResponses, vector<string> incorrectResponses);
	//return the percentage of correct answers the student has given over all questions
	double ReportOnStudentResults();
	//return a question string for a certain constructed state
	MathQuestion CreateQuestion();
	//check a given answer is correct in the given question and respond appropriately to the user
	bool IsAnswerCorrect(MathQuestion question, double givenAnswer);

private:
	ProblemType mProblemType;
	int mDifficulty, mResponseCount, mCorrectCount;
	vector<string> mCorrectResponses, mIncorrectResponses;

	//set the problem type, provided the input is valid
	void setProblemType(int problemType);
	//set the difficulty level, provided the input is valid
	void setDifficultyLevel(int difficulty);
	//set the correct responses, provided the input is valid
	void setCorrectResponses(vector<string> correctResponses);
	//set the incorrect responses, provided the input is valid
	void setIncorrectResponses(vector<string> incorrectResponses);
};

