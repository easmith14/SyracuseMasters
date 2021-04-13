/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
Final Project: Snake
Last Updated: 3 / 29 / 21
This file sets the values of the formatting constants used throughout the game
*/
#include "DrawingConstants.h"

//fonts
const std::string DrwCnst::DEFAULT_FONT = "HARLOWSI.TTF";

//colors
const Color DrwCnst::PRIMARY_COLOR = Color::Yellow;
const Color DrwCnst::LIGHT_ACCENT_COLOR = Color(238, 171, 17, 255);
const Color DrwCnst::DARK_ACCENT_COLOR = Color(190, 137, 10, 255);
const Color DrwCnst::CONTRAST_COLOR = Color::Magenta;
const Color DrwCnst::BACKGROUND_FILL_COLOR = Color(190, 137, 10, 255);
const Color DrwCnst::SCORE_COLOR = Color(0, 0, 0, 180);
const Color DrwCnst::SNAKE_COLOR = Color::White;
const Color DrwCnst::TOGGLE_SELECTION_COLOR = Color::Green;
const Color DrwCnst::TOGGLE_FILL_COLOR = Color(0, 102, 0, 80);
const Color DrwCnst::TOGGLE_ACCENT_COLOR = Color(0, 204, 0, 255);
const Color DrwCnst::DEFAULT_TEXT_COLOR = Color::Black;


//scaling factors

//button
const float DrwCnst::BUTTON_WIDTH_FACTOR = 3.0f;
const float DrwCnst::BUTTON_HEIGHT_FACTOR = 8.0f;
const int DrwCnst::BUTTON_BORDER_THICKNESS = 8;
const int DrwCnst::BUTTON_TEXT_SIZE = 60;
const float DrwCnst::BUTTON_XPOS_FACTOR = 2.0f;
const float DrwCnst::BUTTON_YPOS_FACTOR = 1.2f;

//snake
const float DrwCnst::SNAKE_FACTOR = 0.9f;

//food
const float DrwCnst::FOOD_FACTOR = 0.8f;
const int DrwCnst::FOOD_BORDER_THICKNESS = 4;

//toggles
const float DrwCnst::TOGGLE_WIDTH_FACTOR = 10.0f;
const float DrwCnst::TOGGLE_HEIGHT_FACTOR = 10.0f;
const int DrwCnst::TOGGLE_BORDER_THICKNESS = 15;
const int DrwCnst::TOGGLE_TEXT_SIZE = 40;

const float DrwCnst::TOGGLE_SELECTION_FACTOR = 3.2f;

const float DrwCnst::GRID_TOGGLE_XPOS_FACTOR = 2.5f;
const float DrwCnst::GRID_TOGGLE_YPOS_FACTOR = 2.4f;
const float DrwCnst::SCORE_TOGGLE_XPOS_FACTOR = 2.5f;
const float DrwCnst::SCORE_TOGGLE_YPOS_FACTOR = 1.8f;

//static text
const float DrwCnst::TITLE_TEXT_SIZE = 200;
const float DrwCnst::HIGHSCORE_TEXT_SIZE = 70;

const float DrwCnst::TITLE_XPOS_FACTOR = 2.2f;
const float DrwCnst::TITLE_YPOS_FACTOR = 0.15f;
const float DrwCnst::SUBTITLE_XPOS_FACTOR = 1.7f;
const float DrwCnst::SUBTITLE_YPOS_FACTOR = 0.23f;
const float DrwCnst::HIGHSCORE_DESC_XPOS_FACTOR = 2.25f;
const float DrwCnst::HIGHSCORE_DESC_YPOS_FACTOR = 1.45f;
const float DrwCnst::HIGHSCORE_XPOS_FACTOR = 1.65f;
const float DrwCnst::HIGHSCORE_YPOS_FACTOR = 1.45f;