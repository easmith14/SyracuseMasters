/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
Final Project: Snake
Last Updated: 3 / 29 / 21
This file describes the overall logic controller for the application.
It handles user inputs and manages the controllers for the menu and gameplay
*/
#pragma once
#include <vector>
#include <deque>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "MenuController.h"
#include "GameController.h"

using sf::Event;
using sf::Keyboard;
using sf::Shape;
using sf::Drawable;
using sf::RenderWindow;

using std::vector;
using std::deque;

using std::is_member_function_pointer;
using std::chrono::time_point;
using std::chrono::high_resolution_clock;

class SnakeGameManager
{
public:
	//constructor takes in information about the screen setup to pass to its subcontrollers
	SnakeGameManager(int height, int width, int frameRate, int resolution);
	//when there is a click, pass it to the menu controller to handle
	void HandleClick(int x, int y);
	//when there are unique key presses, add them to the queue of inputs
	void UpdateKeyPressQueue(Keyboard::Key keyPressed);
	//render the current game screen using the appropriate controller
	vector<Drawable*> UpdateScreen();

private:
	//check a timer to decide when to increment the game position
	bool shouldRenderNextFrame();
	//store the queue of key inputs and the most recent one to use
	deque<Keyboard::Key> mKeyPressDeque;
	Keyboard::Key mLastKeyPress;
	//controller for menu logic
	MenuController mMenuController;
	//controller for game logic
	GameController mGameController;
	//stores all of the elements to be drawn on the screen at the next cycle
	vector<Drawable*> mGameScreen;
	//controls whether we are in a game state or a menu state
	bool mIsGameInProgress;
	//benchmark time used to decide when to render the next frame to achieve consisten FR
	time_point<high_resolution_clock> mLastFrameTime;
	//calculated value (inverse of frame rate)
	double mTimePerFrame;
};

