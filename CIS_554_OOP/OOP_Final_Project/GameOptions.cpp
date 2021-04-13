/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
Final Project: Snake
Last Updated: 3 / 29 / 21
This file implements a stateful class that holds the options controlled by the menu
*/
#include "GameOptions.h"

//reset the options to default
GameOptions::GameOptions()
{
	StartGame = false;
	UseGrid = true;
	ShowScore = false;
}
