/*
Evan Smith
CIS 554-M401 Object Oriented Programming in C++
Syracuse University
HW #4 - Exercise 6.57-61 p281
2/22/21
This program describes a class which represents a math question which can have its text retrieved and prospective answers checked.
*/

#pragma once

#include <string>

using std::string;

class MathQuestion
{
public:
	//create a MathQuestion object
	MathQuestion(string question, double correctAnswer);
	//check if a given answer to the question is correct
	bool CheckAnswer(double givenAnswer);
	//allow read-only access to the question
	string GetQuestionText();
private:
	double mCorrectAnswer;
	string mQuestion;
};

