/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
Final Project: Snake
Last Updated: 3 / 29 / 21
This file describes the controller for the menu state of the application
It handles user input and dynamically renders menu items
*/
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "MenuItem.h"

using sf::Drawable;
using sf::Color;
using sf::Text;
using sf::Font;

using std::vector;
using std::string;

class MenuController
{
public:
	//constructor uses screen size to lay out elements
	MenuController(int width, int height);
	//when clicked, take appropriate action
	bool HandleMenuClick(int x, int y);
	//render the menu screen, taking into account dynamic options like score and toggles
	void UpdateMenuScreen(vector<Drawable*> &screen);
	//take in a game score and update high score if needed
	void UpdateHighScore(int newScore);
	//a set of controls that affect the GameController
	GameOptions Options;

private:
	//given basic inputs, create a centered, easily positionable text object
	Text* makeCenterOriginText(string text, int fontSize, Color fontColor);

	//store information about the screen and game
	int mMaxWidth, mMaxHeight, mHighScore;
	//store the font so it only has to be read in only once on creation
	Font mFont;
	//the set of all dynamic user-affectable elements of the menu. Polymorphic!
	vector<MenuItem*> mMenu;
};