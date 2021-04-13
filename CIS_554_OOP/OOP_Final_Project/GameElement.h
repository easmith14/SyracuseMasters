/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
Final Project: Snake
Last Updated: 3 / 29 / 21
This file describes the base virtual class for any element that can be on the game board
*/
#pragma once
#include <vector>
#include "BoardElementType.h"
#include <SFML/Graphics.hpp>

using std::vector;

using sf::Drawable;

class GameElement
{
public:
	//constructor initializes relative size and element type
	GameElement(BoardElementType elementType, int unitSize);
	//adds any drawables associated with this element to the screen
	virtual void MakeDrawable(vector<Drawable*> &screen) = 0;
	//returns the type of this element
	BoardElementType GetType();
protected:
	//store the type
	BoardElementType mType;
	int mUnitSize;
};

