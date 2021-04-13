/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
Final Project: Snake
Last Updated: 3 / 29 / 21
This file describes a GameElement that is one segment of the Snake
*/
#pragma once
#include "GameElement.h"

using sf::Vector2i;

class SnakeBody : public GameElement
{
public:
	//constructor saves the coordinates of this body element and information about its relative size
	SnakeBody(Vector2i location, int unitSize);
	//draw the snake to the screen
	void MakeDrawable(vector<Drawable*> &screen);
	//maintain a memory of the coordinates to help with snake movement
	Vector2i Location;
};

