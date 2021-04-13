/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
Final Project: Snake
Last Updated: 3 / 29 / 21
This file describes a child of MenuItem which holds text, and triggers a bool when clicked
*/
#pragma once
#include "MenuItem.h"

using std::string;

using sf::Text;
using sf::Vector2f;

//a menu item that triggers a boolean on click
class MenuButton : public MenuItem
{
public:
	//constructor takes in a pre-made text and position, along with relative size for drawing
	//option is passed by reference to allow for this button to trigger any event
	MenuButton(int screenWidth, int screenHeight, Vector2f position, Text* buttonText, bool &ownedOption);
	//check if a click is on this element, and trigger option if so
	virtual void HandleClick(int x, int y) override;
	//add the drawable components of the button to the screen
	virtual void AddDrawables(vector<Drawable*>& screen) override;
protected:
	//store the premade text. This helps get around SFML font loading issues
	Text* mButtonText;
	//hold a reference to the option this button controls
	bool &mOwnedOption;
};

