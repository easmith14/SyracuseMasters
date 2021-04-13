/*
Evan Smith
CIS 554-M401 Object Oriented Programming in C++
Syracuse University
HW #4 - Exercise 6.57-61 p281
2/22/21
This program provides academic support for students who want to learn basic arithmetic at varying levels of difficulty
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include "ArithmeticTrainer.h"
#include "UserPrompter.h"
#include "MathQuestion.h"

using std::string;
using std::cout;
using std::cin;
using std::setw;
using std::setfill;

static int HEADER_WIDTH = 50;
static int NUM_QUESTIONS = 10;
static double SUCCESS_CUTOFF = 0.75;
static vector<string> CORRECT_RESPONSES{ "Very good!", "Excellent!", "Nice work!", "Keep up the good work!" };
static vector<string> INCORRECT_RESPONSES{ "No. Please try again.", "Wrong. Try once more.", "Don't give up!", "No. Keep trying." };

int main()
{
	UserPrompter prompter;

	while (true)
	{
		cout << "Welcome to the arithmetic trainer!\n\nAvailable problem types are:\n"
			<< "\t1 - Addition\n"
			<< "\t2 - Subtraction\n"
			<< "\t3 - Multiplication\n"
			<< "\t4 - Division (rounded to 2 decimal places)\n"
			<< "\t5 - Grab Bag!\n\n";

		//ask for for problem type, or -1 for exit
		int problemType = prompter.promptForNonNegativeIntOrSentinal("Enter Problem Type code, or -1 to exit: ", -1);

		if (problemType == -1)
		{
			break;
		}

		//ask for difficulty level
		int difficultyLevel = prompter.promptForPositiveInt("Enter a Difficulty Level of at least 1: ");

		//create trainer with input and givens
		ArithmeticTrainer trainer(problemType, difficultyLevel, CORRECT_RESPONSES, INCORRECT_RESPONSES);

		//ask questions until required number of questions have been answered successfully
		for (int i = 1; i <= NUM_QUESTIONS; i++)
		{
			//generate question
			MathQuestion question = trainer.CreateQuestion();

			cout << setfill('-') << setw(HEADER_WIDTH) << "-\n";
			cout << setfill(' ') << setw(HEADER_WIDTH/2) << "Question #" << i << "\n";
			cout << setfill('-') << setw(HEADER_WIDTH) << "-\n";

			//get user input and check it until correct
			double userAnswer = prompter.promptForDouble(question.GetQuestionText() +  " = ");
			
			while (!trainer.IsAnswerCorrect(question, userAnswer))
			{
				userAnswer = prompter.promptForDouble(question.GetQuestionText() + " = ");
			}
		}

		//decide whether student is proficient or not and tell them so
		double score = trainer.ReportOnStudentResults();

		cout << "\n" << setfill('*') << setw(HEADER_WIDTH) << "*\n"
			<< "Your score was " << round(score * 100) << "%\n";

		if (score < SUCCESS_CUTOFF)
		{
			cout << "Please ask your teacher for extra help.";
		}
		else
		{
			cout << "Congratulations, you are ready to go to the next level!";
		}

		cout << "\n" << setfill('*') << setw(HEADER_WIDTH+3) << "*\n\n\n\n";
	}


}