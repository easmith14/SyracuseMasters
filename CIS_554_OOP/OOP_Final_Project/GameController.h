/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
Final Project: Snake
Last Updated: 3 / 29 / 21
This file describes the controller for the game state of the application
It handles user input, tracks the location of game elements, and listens for game overs
*/
#pragma once
#include <vector>
#include <deque>
#include <SFML/Graphics.hpp>
#include "BoardElementType.h"
#include "GameElement.h"
#include "SnakeBody.h"
#include "SnakeFood.h"
#include "GameOptions.h"

using sf::Keyboard;
using sf::Font;
using sf::Drawable;

using std::vector;
using std::deque;
using std::map;

class GameController
{
public:
	//constructor calculates the size of the gameboard and initializes components
	GameController(int width, int height, int unitSize);
	//given an input, this increments snake movement and draws the resulting board
	bool UpdateGameScreen(Keyboard::Key userInput, vector<Drawable*> &screen);
	//returns the score
	int GetScore();
	//mimics much of the constructor component initialization to allow for reuse of the controller
	void ResetGame();
	//A set of options set from the MenuController
	GameOptions Options;
private:
	//update snake head position
	void updateSnakeHead(Keyboard::Key userInput);
	//check for collisions
	bool checkCollisions();
	//store information about the board and score
	int mUnitWidth, mUnitHeight, mUnitSize, mSnakeLength;
	//store font information to allow for a single file read
	Font mFont;
	//keep track of previous input to prevent instant loss (folding back on yourself)
	Keyboard::Key mLastUserInput;
	//a map of all elements in the game, indexed by coordinate
	map<vector<int>,GameElement*> mGameBoard;
	//the set of body elements that make up the snake. Used to track head and tail
	deque<SnakeBody> mSnake;
	//a reusable game element that triggers snake growth and can reposition itself into a free game space
	SnakeFood mFood;
};

