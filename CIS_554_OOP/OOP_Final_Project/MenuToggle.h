/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
Final Project: Snake
Last Updated: 3 / 29 / 21
This file describes a toggle element, which is clickable and stores/displays state
*/
#pragma once
#include "MenuButton.h"

//child of a button, but with state
class MenuToggle : public MenuButton
{
public:
	//constructor is the same as button
	MenuToggle(int screenWidth, int screenHeight, Vector2f position, Text* toggleText, bool &ownedOption)
		: MenuButton(screenWidth, screenHeight, position, toggleText, ownedOption) {}
	//decide if the toggle has been clicked and react accordingly
	void HandleClick(int x, int y);
	//add the toggle drawables to the screen
	void AddDrawables(vector<Drawable*>& screen);
};

