/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
Final Project: Snake
Last Updated: 3 / 29 / 21
This file specifies the formatting constants to be used throughout the game
*/
#pragma once
#include <SFML/Graphics.hpp>

using sf::Color;

class DrwCnst
{
public:
	//fonts
	static const std::string DEFAULT_FONT;

	//colors
	static const Color PRIMARY_COLOR;
	static const Color LIGHT_ACCENT_COLOR;
	static const Color DARK_ACCENT_COLOR;
	static const Color CONTRAST_COLOR;
	static const Color BACKGROUND_FILL_COLOR;
	static const Color SCORE_COLOR;
	static const Color SNAKE_COLOR;
	static const Color TOGGLE_SELECTION_COLOR;
	static const Color TOGGLE_FILL_COLOR; 
	static const Color TOGGLE_ACCENT_COLOR;
	static const Color DEFAULT_TEXT_COLOR;

	//scaling factors

	//button
	static const float BUTTON_WIDTH_FACTOR;
	static const float BUTTON_HEIGHT_FACTOR;
	static const int BUTTON_BORDER_THICKNESS;
	static const int BUTTON_TEXT_SIZE;
	static const float BUTTON_XPOS_FACTOR;
	static const float BUTTON_YPOS_FACTOR;

	//snake
	static const float SNAKE_FACTOR;

	//food
	static const float FOOD_FACTOR;
	static const int FOOD_BORDER_THICKNESS;

	//toggles
	static const float TOGGLE_WIDTH_FACTOR;
	static const float TOGGLE_HEIGHT_FACTOR;
	static const int TOGGLE_BORDER_THICKNESS;
	static const int TOGGLE_TEXT_SIZE;

	static const float TOGGLE_SELECTION_FACTOR;

	static const float GRID_TOGGLE_XPOS_FACTOR;
	static const float GRID_TOGGLE_YPOS_FACTOR;	
	static const float SCORE_TOGGLE_XPOS_FACTOR;
	static const float SCORE_TOGGLE_YPOS_FACTOR;

	//static text
	static const float TITLE_TEXT_SIZE;
	static const float HIGHSCORE_TEXT_SIZE;

	static const float TITLE_XPOS_FACTOR;
	static const float TITLE_YPOS_FACTOR;
	static const float SUBTITLE_XPOS_FACTOR;
	static const float SUBTITLE_YPOS_FACTOR;
	static const float HIGHSCORE_DESC_XPOS_FACTOR;
	static const float HIGHSCORE_DESC_YPOS_FACTOR;
	static const float HIGHSCORE_XPOS_FACTOR;
	static const float HIGHSCORE_YPOS_FACTOR;
};

