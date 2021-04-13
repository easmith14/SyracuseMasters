/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
Final Project: Snake
Last Updated: 3 / 29 / 21
This file implements the overall logic controller for the application.
It handles user inputs and manages the controllers for the menu and gameplay
*/

#include <iostream>
#include "SnakeGameManager.h"

//constructor takes in information about the screen setup to pass to its subcontrollers
SnakeGameManager::SnakeGameManager(const int height, const int width, const int frameRate, const int resolution)
:mMenuController(width, height), mGameController(width, height, resolution)
{
	mLastKeyPress = Keyboard::Key::Up;
	mIsGameInProgress = false;
	mTimePerFrame = 1.0 / frameRate;
}

//when there is a click, pass it to the menu controller to handle
void SnakeGameManager::HandleClick(int x, int y)
{
	mIsGameInProgress = mMenuController.HandleMenuClick(x, y);

	//if we are starting a new game, do some reset behavior
	if (mIsGameInProgress)
	{
		//update the gameController with the new options
		mGameController.Options = mMenuController.Options;
		mMenuController.Options.StartGame = false;
	}
}

//when there are unique key presses, add them to the queue of inputs
//this queuing allows for inputs faster than the frame rate to register
//and allows players to tap the input rather than hold it
void SnakeGameManager::UpdateKeyPressQueue(Keyboard::Key keyPressed)
{
	//only store keypresses if we are in the game vs the menu
	if (mIsGameInProgress)
	{
		//don't store duplicate presses
		if (mKeyPressDeque.size() == 0 || mKeyPressDeque.back() != keyPressed)
		{
			mKeyPressDeque.push_back(keyPressed);
		}
	}
}

//this function is called to render the current game screen using the appropriate controller
vector<Drawable*> SnakeGameManager::UpdateScreen()
{	
	//if we are in the game state and it is time to update the location of the objects
	if (mIsGameInProgress && shouldRenderNextFrame())
	{
		//set the current key press to be the top of the deque
		mGameScreen.clear();
		if (mKeyPressDeque.size() > 0)
		{
			mLastKeyPress = mKeyPressDeque.front();
			mKeyPressDeque.pop_front();
		}
		//render the next position of the game, and store whether it is game over
		mIsGameInProgress = mGameController.UpdateGameScreen(mLastKeyPress, mGameScreen);

		//if we are ending a game, do some reset behavior
		if (!mIsGameInProgress)
		{
			//log the last game's score into the Menu Record
			mMenuController.UpdateHighScore(mGameController.GetScore());

			//reset the gameController's options
			mGameController.ResetGame();
		}
	}
	//else, we are in the menu state. Let the menu update itself on every cycle, framerate is no issue here
	else if(!mIsGameInProgress)
	{ 
		mGameScreen.clear();
		mMenuController.UpdateMenuScreen(mGameScreen);
	}

	return mGameScreen;
}

//a private function to check a timer to decide when to increment the game position
bool SnakeGameManager::shouldRenderNextFrame()
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = currentTime - mLastFrameTime;

	//if it is time to increment, set the current time as the new benchmark
	if (elapsed.count() >= mTimePerFrame)
	{
		mLastFrameTime = currentTime;
		return true;
	}
	//else we don't read an input or update the screen
	else return false;
}
