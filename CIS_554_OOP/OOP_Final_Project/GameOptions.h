/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
Final Project: Snake
Last Updated: 3 / 29 / 21
This file describes a stateful class that holds the options controlled by the menu
*/
#pragma once
class GameOptions
{
public:
	//constructor simply resets options to default
	GameOptions();
	//store options here
	bool StartGame, UseGrid, ShowScore;
};

