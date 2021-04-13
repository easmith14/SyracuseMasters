/*
Evan Smith
CIS 554-M401 Object Oriented Programming in C++
Syracuse University
HW #4 - Exercise 6.57-61 p281
2/22/21
This program implements a trainer which creates math questions based on input parameters,
and tracks student's progress in their answers
*/

#include <vector>
#include <string>
#include <iostream>
#include "ArithmeticTrainer.h"
#include "MathQuestion.h"
#include "ProblemType.h"

using std::string;
using std::vector;
using std::cout;
using std::to_string;

//create an ArithmeticTrainer while validating inputs
ArithmeticTrainer::ArithmeticTrainer(int problemType, int difficulty, vector<string> correctResponses, vector<string> incorrectResponses)
	: mCorrectCount(0), mResponseCount(0)
{
	setProblemType(problemType);
	setDifficultyLevel(difficulty);
	setCorrectResponses(correctResponses);
	setIncorrectResponses(incorrectResponses);
}

//return the percentage of correct responses out of total responses by the student
//if an invalid number of questions have been asked, 
double ArithmeticTrainer::ReportOnStudentResults()
{
	double grade = 0.0;

	if (mResponseCount > 0)
	{
		grade = (mCorrectCount * 1.0) / mResponseCount;
	}
	
	return grade;
}

//create a MathQuestion using the class variables that decide the size of the given integers and the operation requested
MathQuestion ArithmeticTrainer::CreateQuestion()
{
	//generate 2 random positive integers that are < than 10^difficulty
	srand(time(NULL));
	int num1 = rand() % (int)pow(10.0, mDifficulty);
	int num2 = rand() % (int)pow(10.0, mDifficulty);

	//copy the problem type to allow for selection of a random type if the GrabBag option was chosen
	ProblemType switchableProblemType = mProblemType;
	if (switchableProblemType == ProblemType::GrabBag)
	{
		switchableProblemType = static_cast<ProblemType>((rand() % 4) + 1);
	}

	//populate the operator and correct answer depending on the selected problem type
	string operatorText = "";
	double answer = 0.0;

	switch (switchableProblemType)
	{
	case ProblemType::Addition: 
		operatorText = " + "; 
		answer = (num1 * 1.0) + num2;
		break;
	case ProblemType::Subtraction:
		operatorText = " - ";
		answer = (num1 * 1.0) - num2;
		break;
	case ProblemType::Multiplication:
		operatorText = " * ";
		answer = (num1 * 1.0) * num2;
		break;
	//for the division case we must enforce the denominator != 0
	case ProblemType::Division:
		operatorText = " / ";

		//if denominator is 0, we set it to a random value enforced >0 but within the difficulty range
		if(num2 == 0)
		{
			num2 = 1 + (rand() % ((int)pow(10, mDifficulty) - 1));
		}

		answer = (num1 * 1.0) / num2;
		break;
	}

	//populate the question string
	string questionText = to_string(num1) + operatorText + to_string(num2);

	return MathQuestion(questionText, answer);
}

//check to see if the given answer is correct, update statistics, and then respond with the appropriate random response
bool ArithmeticTrainer::IsAnswerCorrect(MathQuestion question, double givenAnswer)
{
	//we increment the response count no matter what
	mResponseCount++;

	bool isCorrect = question.CheckAnswer(givenAnswer);

	srand(time(NULL));
	//based on correctness, we select a random response from the proper response list
	if (isCorrect)
	{
		mCorrectCount++;
		int index = (int)rand() % mCorrectResponses.size();
		cout << mCorrectResponses[index] << "\n";
	}
	else
	{
		int index = (int)rand() % mIncorrectResponses.size();
		cout << mIncorrectResponses[index] << "\n";
	}

	return isCorrect;
}

//set the problem type if valid, else default to Addition
void ArithmeticTrainer::setProblemType(int problemType)
{
	ProblemType parsedProblemType = ProblemType::Addition;

	if (problemType >= 1 && problemType <= 5)
	{
		parsedProblemType = static_cast<ProblemType>(problemType);
	}
	
	mProblemType = parsedProblemType;
}

//set the difficulty if valid, else default to 1
void ArithmeticTrainer::setDifficultyLevel(int difficulty)
{
	if (difficulty > 0)
	{
		mDifficulty = difficulty;
	}
	else
	{
		mDifficulty = 1;
	}
}
//set the correct responses if valid, else default to "Correct!"
void ArithmeticTrainer::setCorrectResponses(vector<string> correctResponses)
{
	if (correctResponses.size() > 0)
	{
		mCorrectResponses = correctResponses;
	}
	else
	{
		mCorrectResponses = vector<string>{ "Correct!" };
	}
}
//set the incorrect responses if valid, else default to "Incorrect, try again."
void ArithmeticTrainer::setIncorrectResponses(vector<string> incorrectResponses)
{
	if (incorrectResponses.size() > 0)
	{
		mIncorrectResponses = incorrectResponses;
	}
	else
	{
		mIncorrectResponses = vector<string>{ "Incorrect, try again." };
	}
}
