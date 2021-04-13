/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
Final Project: Snake
Last Updated: 3 / 29 / 21
This file implements the base virtual class for any element that can be on the game board
*/
#include "GameElement.h"

//constructor initializes relative size and element type
GameElement::GameElement(BoardElementType elementType, int unitSize)
:mType(elementType), mUnitSize(unitSize)
{
}

//returns the type of this element
BoardElementType GameElement::GetType()
{
	return mType;
}
