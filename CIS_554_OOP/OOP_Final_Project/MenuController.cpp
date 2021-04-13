/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
Final Project: Snake
Last Updated: 3 / 29 / 21
This file implements the controller for the menu state of the application
It handles user input and dynamically renders menu items
*/
#include "MenuController.h"
#include "MenuButton.h"
#include "MenuToggle.h"
#include "DrawingConstants.h"

//constructor uses screen size to lay out elements
MenuController::MenuController(int width, int height)
:mMaxWidth(width), mMaxHeight(height), mHighScore(0)
{
	//load in the font once and save it for all future elements to use
	mFont.loadFromFile(DrwCnst::DEFAULT_FONT);

	//add all the menu elements with location and labels
	mMenu.push_back(new MenuButton(width, height, Vector2f(width / DrwCnst::BUTTON_XPOS_FACTOR, 
														   height / DrwCnst::BUTTON_YPOS_FACTOR), 
					makeCenterOriginText("Start!", DrwCnst::BUTTON_TEXT_SIZE, DrwCnst::DEFAULT_TEXT_COLOR), 
					Options.StartGame));
	mMenu.push_back(new MenuToggle(width, height, Vector2f(width / DrwCnst::GRID_TOGGLE_XPOS_FACTOR, 
														   height / DrwCnst::GRID_TOGGLE_YPOS_FACTOR),
					makeCenterOriginText("Show Grid", DrwCnst::TOGGLE_TEXT_SIZE, DrwCnst::PRIMARY_COLOR),
					Options.UseGrid));
	mMenu.push_back(new MenuToggle(width, height, Vector2f(width / DrwCnst::SCORE_TOGGLE_XPOS_FACTOR,
														   height / DrwCnst::SCORE_TOGGLE_YPOS_FACTOR),
					makeCenterOriginText("Show Score", DrwCnst::TOGGLE_TEXT_SIZE, DrwCnst::PRIMARY_COLOR),
					Options.ShowScore));
}

//when clicked, take appropriate action
bool MenuController::HandleMenuClick(int x, int y)
{
	//iterate over all buttons in menu, calling HandleClick on each to potentially update options
	for (MenuItem* item : mMenu)
	{
		item->HandleClick(x, y);
	}

	return Options.StartGame;
}

//render the menu screen, taking into account dynamic options like score and toggles
void MenuController::UpdateMenuScreen(vector<Drawable*> &screen)
{
	//create static components (title, background)

	//title
	Text* title = makeCenterOriginText("Snake", DrwCnst::TITLE_TEXT_SIZE, Color::Yellow);
	title->setPosition(mMaxWidth / DrwCnst::TITLE_XPOS_FACTOR, 
					   mMaxHeight * DrwCnst::TITLE_YPOS_FACTOR);
	screen.push_back(title);

	//subtitle
	Text* subtitle = makeCenterOriginText("A Final Project For CIS 554", DrwCnst::TOGGLE_TEXT_SIZE, DrwCnst::LIGHT_ACCENT_COLOR);
	subtitle->setPosition(mMaxWidth / DrwCnst::SUBTITLE_XPOS_FACTOR, 
						  mMaxHeight * DrwCnst::SUBTITLE_YPOS_FACTOR);
	screen.push_back(subtitle);

	//high score message, if needed
	if (mHighScore > 0)
	{
		Text* highScoreText = makeCenterOriginText("High Score:", DrwCnst::TOGGLE_TEXT_SIZE, DrwCnst::PRIMARY_COLOR);
		highScoreText->setPosition(mMaxWidth / DrwCnst::HIGHSCORE_DESC_XPOS_FACTOR, 
								   mMaxHeight / DrwCnst::HIGHSCORE_DESC_YPOS_FACTOR);
		screen.push_back(highScoreText);

		Text* highScore = makeCenterOriginText(std::to_string(mHighScore), DrwCnst::HIGHSCORE_TEXT_SIZE, DrwCnst::CONTRAST_COLOR);
		highScore->setPosition(mMaxWidth / DrwCnst::HIGHSCORE_XPOS_FACTOR, 
							   mMaxHeight / DrwCnst::HIGHSCORE_YPOS_FACTOR);
		screen.push_back(highScore);
	}

	//get shape from each of the MenuItems
	for (MenuItem* item : mMenu)
	{
		item->AddDrawables(screen);
	}
}

//take in a game score and update high score if needed
void MenuController::UpdateHighScore(int newScore)
{
	if (newScore > mHighScore)
	{
		mHighScore = newScore;
	}
}

//given basic inputs, create a centered, easily positionable text object
//this is important because it centralizes code and eliminates the need to pass the font into MenuItems
Text* MenuController::makeCenterOriginText(string text, int fontSize, Color fontColor)
{
	//load text
	Text* drawableText = new Text(text, mFont, fontSize);
	drawableText->setFillColor(fontColor);
	//center text
	FloatRect textRect = drawableText->getLocalBounds();
	drawableText->setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	return drawableText;
}
