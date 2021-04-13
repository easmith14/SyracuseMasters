/*
Evan Smith
CIS 554-M401 Object Oriented Programming in C++
Syracuse University
HW #4 - Exercise 6.57-61 p281
2/22/21
This program implements a class which represents a math question which can have its text retrieved and prospective answers checked.
*/

#include "MathQuestion.h"

//creates a MathQuestion object and populates required data
MathQuestion::MathQuestion(string question, double correctAnswer)
	: mQuestion(question), mCorrectAnswer(correctAnswer)
{

}

//check the provided answer against the stored correct answer, rounded to 2 decimal places. 
//This allows for division answers to be possible for random values
bool MathQuestion::CheckAnswer(double givenAnswer)
{
	return (int)round(givenAnswer * 100) == (int)round(mCorrectAnswer * 100);
}

//return the question string
string MathQuestion::GetQuestionText()
{
	return mQuestion;
}
