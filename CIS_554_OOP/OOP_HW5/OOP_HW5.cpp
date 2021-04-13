/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
HW 5 : MasterMind
3/1/21
The main program for playing a MasterMind game with customizable configurations
*/

#include <iostream>
#include "UserPrompter.h"
#include "MasterMindGameController.h"
#include "MasterMindCombination.h"
#include "MasterMindResponse.h"

using std::cout;
using std::cin;
using std::string;

int main()
{
    cout << "Welcome to MasterMind, ASCII edition!\n\n";
    UserPrompter prompter;

    bool roundsShouldContinue = true;
    while (roundsShouldContinue)
    {
        //ask for start, how to play, or exit
        string choice = prompter.promptForChoice("What would you like to do?\n", vector<string>{"Start Game", "How To Play", "Exit"});

        if (choice == "Exit")
        {
            roundsShouldContinue = false;
        }
        else if (choice == "How To Play")
        {
            cout << "\nOn each turn, guess a set of 4 numbers from 1-6 in the format ""xxxx""\n";
            cout << "You will be told how many of your guesses are the right number in the right place (exact matches).\n";
            cout << "You will also be told how many are the right number but in the wrong place (approx matches).\n";
            cout << "Guess the random pattern of numbers within the turn limit to win! Good Luck!\n\n";
        }
        else
        {
            //make a new game controller
            int maxGuesses = prompter.promptForPositiveInt("Enter the maximum number of guesses the player has: ");
            MasterMindGameController controller(maxGuesses);

            //prompt for guesses and check them, so long as the game is not over
            bool gameOver = false;
            int guessCount = 1;
            do
            {
                string rawCombination = prompter.promptForStringWithApprovedChars("Enter Guess #" + std::to_string(guessCount++) + ": ", vector<char>{'1', '2', '3', '4', '5', '6'});
                MasterMindCombination guess(rawCombination);

                MasterMindResponse response = controller.ExecuteUserTurn(&guess);
                cout << "\t\t\t" + guess.CreateFormattedCombinationString();
                cout << response.CreateFormattedResponse();
                gameOver = response.IsGameOver();
            }
            while (!gameOver);
            

            //give appropriate game ending response, offer play again
            cout << controller.PopulateSummaryString();

            string choice = prompter.promptForChoice("What would you like to do?\n", vector<string>{"Play Again", "Exit"});

            roundsShouldContinue = choice == "Play Again";
        }
    }

}
