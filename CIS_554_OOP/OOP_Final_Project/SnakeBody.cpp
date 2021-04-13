/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
Final Project: Snake
Last Updated: 3 / 29 / 21
This file implements a GameElement that is one segment of the Snake
*/
#include "SnakeBody.h"
#include "DrawingConstants.h"

using sf::Vector2f;
using sf::Color;
using sf::RectangleShape;

//constructor saves the coordinates of this body element and information about its relative size
//it also initializes the type
SnakeBody::SnakeBody(Vector2i location, int unitSize)
	:GameElement(BoardElementType::Snake, unitSize), Location(location)
{
}

//draw the snake to the screen
void SnakeBody::MakeDrawable(vector<Drawable*> &screen)
{
	RectangleShape *snakeShape = new RectangleShape(Vector2f(mUnitSize*DrwCnst::SNAKE_FACTOR, mUnitSize* DrwCnst::SNAKE_FACTOR));
	snakeShape->setFillColor(DrwCnst::SNAKE_COLOR);
	snakeShape->setPosition(Location.x, Location.y);

	screen.push_back(snakeShape);
}
