/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
Final Project: Snake
Last Updated: 3 / 29 / 21
This file implements a GameElement that is the "food" for the Snake
*/
#include <ctime>
#include "SnakeFood.h"
#include "DrawingConstants.h"

using std::srand;
using std::rand;

using sf::Color;
using sf::Vector2f;
using sf::CircleShape;
using sf::RectangleShape;

//constructor takes in information about the screen for sizing and locating
//initializes element type and location
SnakeFood::SnakeFood(int unitSize, int unitWidth, int unitHeight)
:GameElement(BoardElementType::Food, unitSize), mUnitWidth(unitWidth), mUnitHeight(unitHeight)
{
	mLocation = vector<int>{ 0, 0 };
}

//draw food to the screen
void SnakeFood::MakeDrawable(vector<Drawable*> &screen)
{
	RectangleShape *foodShape = new RectangleShape(Vector2f(mUnitSize * DrwCnst::FOOD_FACTOR, 
															mUnitSize * DrwCnst::FOOD_FACTOR));
	foodShape->setFillColor(DrwCnst::PRIMARY_COLOR);
	foodShape->setOutlineColor(DrwCnst::LIGHT_ACCENT_COLOR);
	foodShape->setOutlineThickness(DrwCnst::FOOD_BORDER_THICKNESS);
	foodShape->setPosition(mLocation[0], mLocation[1]);
	screen.push_back(foodShape);
}

//given the current gameboard, find an open spot to relocate the food to
void SnakeFood::MoveToNextLocation(map<vector<int>, GameElement*> &gameBoard)
{
	//build up list of all possible locations
	vector<vector<int>> possibleFoodLocations;

	for (int x=0; x<mUnitWidth; x++)
	{
		for (int y = 0; y < mUnitHeight; y++)
		{
			vector<int> potentialLocation{ x * mUnitSize, y * mUnitSize};

			//we only consider a location if it has no elements in it right now
			if (gameBoard.count(potentialLocation) == 0)
			{
				possibleFoodLocations.push_back(potentialLocation);
			}
		}
	}

	//select a random element from the possible locations
	srand(time(NULL));
	int randomIndex = rand() % possibleFoodLocations.size();

	mLocation = possibleFoodLocations[randomIndex];
	gameBoard[mLocation] = this;
}
