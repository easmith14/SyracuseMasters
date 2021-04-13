/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
Final Project: Snake
Last Updated: 3 / 29 / 21
This file describes the base virtual class for an interactable menu element
*/
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameOptions.h"

using std::vector;

using sf::Drawable;
using sf::FloatRect;
using sf::Vector2f;

class MenuItem
{
public:
	//constructor takes in information about screen and positioning, and initialized the bounding box
	MenuItem(int screenWidth, int screenHeight, Vector2f position) 
		: mScreenWidth(screenWidth), mScreenHeight(screenHeight), mPosition(position), mBoundingBox(){};
	//uses the bounding box to decide if clicked, then take action if needed
	virtual void HandleClick(int x, int y) = 0;
	//display any drawables associated with this element
	virtual void AddDrawables(vector<Drawable*> &screen) = 0;
protected:
	//store screen and position information
	int mScreenWidth, mScreenHeight;
	Vector2f mPosition;
	//store bounding box, which is updated whenever the element is drawn to screen
	FloatRect mBoundingBox;
};

