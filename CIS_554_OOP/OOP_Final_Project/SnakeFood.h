/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
Final Project: Snake
Last Updated: 3 / 29 / 21
This file describes a GameElement that is the "food" for the Snake
*/
#pragma once
#include "GameElement.h"
#include <map>
#include <vector>

using std::map;
using std::vector;

class SnakeFood : public GameElement
{
public:
	//constructor takes in information about the screen for sizing and locating
	SnakeFood(int unitSize, int unitWidth, int unitHeight);
	//draw food to the screen
	void MakeDrawable(vector<Drawable*> &screen);
	//given the current gameboard, find an open spot to relocate the food to
	void MoveToNextLocation(map<vector<int>, GameElement*> &gameBoard);

private:
	//the current location of the food
	vector<int> mLocation;
	//the size of the coordinate grid
	int mUnitWidth, mUnitHeight;
};

