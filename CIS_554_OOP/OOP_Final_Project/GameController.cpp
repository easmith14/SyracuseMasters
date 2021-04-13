/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
Final Project: Snake
Last Updated: 3 / 29 / 21
This file implements the controller for the game state of the application
It handles user input, tracks the location of game elements, and listens for game overs
*/
#include "GameController.h"
#include "DrawingConstants.h"

using sf::RectangleShape;
using sf::Vector2f;
using sf::Vector2i;
using sf::Color;
using sf::Text;
using sf::FloatRect;

//constructor calculates the size of the gameboard and initializes components
GameController::GameController(int width, int height, int unitSize)
	: mUnitWidth(width / unitSize),
	mUnitHeight(height / unitSize),
	mLastUserInput(Keyboard::Key::Up),
	mSnake{ SnakeBody(Vector2i(width / 2, height / 2), unitSize) },
	mSnakeLength(1),
	mUnitSize(unitSize),
	mFood(unitSize, mUnitWidth, mUnitWidth)
{
	//add the snake and food to the gameboard
	mGameBoard[vector<int>{mSnake.front().Location.x, mSnake.front().Location.y}] = &(mSnake.front());
	mFood.MoveToNextLocation(mGameBoard);
	//load font for use in render cycles
	mFont.loadFromFile(DrwCnst::DEFAULT_FONT);
}

//given an input, increment snake movement and draw the resulting board
bool GameController::UpdateGameScreen(Keyboard::Key userInput, vector<Drawable*> &screen)
{
	//update snake head position
	updateSnakeHead(userInput);

	//check for collisions
	bool isGameContinuing = checkCollisions();

	//if should show grid, draw all possible squares
	if (Options.UseGrid)
	{
		for (int x = 0; x < mUnitWidth; x++)
		{
			for (int y = 0; y < mUnitHeight; y++)
			{
				RectangleShape* gridSquare = new RectangleShape(Vector2f(mUnitSize, mUnitSize));
				gridSquare->setFillColor(Color::Transparent);
				gridSquare->setOutlineColor(DrwCnst::CONTRAST_COLOR);
				gridSquare->setOutlineThickness(1);
				gridSquare->setPosition(x * mUnitSize, y * mUnitSize);

				screen.push_back(gridSquare);
			}
		}
	}

	//make the shapes for all elements in GameBoard and push to the GameScreen
	for (auto gameElementEntry : mGameBoard)
	{
		gameElementEntry.second->MakeDrawable(screen);
	}

	//if should display score, draw it on the head of the snake
	if (Options.ShowScore)
	{
		//load text
		Text* drawableText = new Text(std::to_string(mSnakeLength), mFont, 50);
		drawableText->setFillColor(DrwCnst::SCORE_COLOR);
		//center text
		FloatRect textRect = drawableText->getLocalBounds();
		drawableText->setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		//position text

		drawableText->setPosition(mSnake.front().Location.x + (mUnitSize/2 * DrwCnst::SNAKE_FACTOR), 
								  mSnake.front().Location.y + (mUnitSize / 2 * DrwCnst::SNAKE_FACTOR));

		screen.push_back(drawableText);
	}

    return isGameContinuing;
}

//returns the score
int GameController::GetScore()
{
	return mSnakeLength;
}

//mimics much of the constructor component initialization to allow for reuse of the controller
void GameController::ResetGame()
{
	//reset options
	Options = GameOptions();
	//reset snake
	mSnake.clear();
	mSnake.push_back(SnakeBody(Vector2i(mUnitWidth * mUnitSize / 2, mUnitHeight * mUnitSize / 2), mUnitSize));
	mSnakeLength = 1;
	//reset game board
	mGameBoard.clear();
	mGameBoard[vector<int>{mSnake.front().Location.x, mSnake.front().Location.y}] = &(mSnake.front());
	//reset food
	mFood.MoveToNextLocation(mGameBoard);
	//reset last input
	mLastUserInput = Keyboard::Key::Up;
}

//add new snake body in the direction of travel (wrap if needed)
void GameController::updateSnakeHead(Keyboard::Key userInput)
{
	//set direction based on user input
	//ignore direct backtracks, must turn or continue.
	Vector2i direction(0, 0);

	switch (userInput)
	{
	case Keyboard::Key::Left:
		if(mLastUserInput == Keyboard::Key::Right) direction = Vector2i(mUnitSize, 0);
		else
		{
			direction = Vector2i(-mUnitSize, 0);
			mLastUserInput = userInput;
		}
		break;
	case Keyboard::Key::Right:
		if (mLastUserInput == Keyboard::Key::Left) direction = Vector2i(-mUnitSize, 0);
		else {
			direction = Vector2i(mUnitSize, 0);
			mLastUserInput = userInput;
		}
		break;
	case Keyboard::Key::Up:
		if (mLastUserInput == Keyboard::Key::Down) direction = Vector2i(0, mUnitSize);
		else{
			direction = Vector2i(0, -mUnitSize);
			mLastUserInput = userInput;
		}
		break;
	case Keyboard::Key::Down:
		if (mLastUserInput == Keyboard::Key::Up) direction = Vector2i(0, -mUnitSize);
		else {
			direction = Vector2i(0, mUnitSize);
			mLastUserInput = userInput;
		}
		break;
	}

	//increment next snake location using direction
	auto nextLocation = mSnake.front().Location + direction;

	//wrapping logic (if over edge of the board, show up on the other side)
	if (nextLocation.x < 0) nextLocation.x += (mUnitWidth * mUnitSize);
	if (nextLocation.x >= mUnitWidth * mUnitSize) nextLocation.x = 0;
	if (nextLocation.y < 0) nextLocation.y += (mUnitHeight * mUnitSize);
	if (nextLocation.y >= mUnitHeight * mUnitSize) nextLocation.y = 0;

	//add the new snake head
	SnakeBody newHead = SnakeBody(nextLocation, mUnitSize);
	mSnake.push_front(newHead);
}

//check for collisions between the snake head and other game elements
bool GameController::checkCollisions()
{
	bool isGameContinuing = true;

	//check for collisions (we need to use a vector conversion due to limitations of the SFML vector library)
	vector<int> snakeHeadLocation{ mSnake.front().Location.x, mSnake.front().Location.y};


	if (mGameBoard.count((vector<int>)snakeHeadLocation) > 0)
	{
		GameElement* potentialCollision = mGameBoard.at(snakeHeadLocation);

		//if bomb or self, end game and reset snake
		if (potentialCollision->GetType() == BoardElementType::Snake)
		{
			isGameContinuing = false;
		}

		//if food, do not remove tail and add a new food piece in an unoccupied square
		else if (potentialCollision->GetType() == BoardElementType::Food)
		{
			mFood.MoveToNextLocation(mGameBoard);
			mSnakeLength++;
		}
	}
	//if no elements collided with, remove tail
	else
	{
		vector<int> snakeTailLocation{ mSnake.back().Location.x, mSnake.back().Location.y };
		//remove from board
		mGameBoard.erase(snakeTailLocation);
		//remove from snake
		mSnake.pop_back();
	}

	//add snake head to board regardless of collision after collisions calculated
	mGameBoard[snakeHeadLocation] = &(mSnake.front());

	return isGameContinuing;
}
