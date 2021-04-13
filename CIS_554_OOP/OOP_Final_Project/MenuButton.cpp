/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
Final Project: Snake
Last Updated: 3 / 29 / 21
This file implements a child of MenuItem which holds text, and triggers a bool when clicked
*/
#include "MenuButton.h"
#include "DrawingConstants.h"

using sf::RectangleShape;
using sf::Color;

//constructor takes in a pre-made text and position, along with relative size for drawing
//option is passed by reference to allow for this button to trigger any event
MenuButton::MenuButton(int screenWidth, int screenHeight, Vector2f position, Text* buttonText, bool &ownedOption)
:mButtonText(buttonText), mOwnedOption(ownedOption), MenuItem(screenWidth, screenHeight, position)
{
}
//check if a click is on this element, and trigger option if so
//use the bounding box of the button rectangle
void MenuButton::HandleClick(int x, int y)
{
    if (mBoundingBox.contains(Vector2f(x, y)))
    {
        mOwnedOption = true;
    }
}

//add the drawable components of the button to the screen
void MenuButton::AddDrawables(vector<Drawable*> &screen)
{
    //make button background
    RectangleShape* buttonBackground = new RectangleShape(Vector2f(mScreenWidth / DrwCnst::BUTTON_WIDTH_FACTOR, 
                                                                   mScreenHeight / DrwCnst::BUTTON_HEIGHT_FACTOR));
    buttonBackground->setFillColor(DrwCnst::LIGHT_ACCENT_COLOR);
    buttonBackground->setOutlineColor(DrwCnst::DARK_ACCENT_COLOR);
    buttonBackground->setOutlineThickness(DrwCnst::BUTTON_BORDER_THICKNESS);

    //center origin and record bounding box
    FloatRect localBoundingBox = buttonBackground->getLocalBounds();
    buttonBackground->setOrigin(localBoundingBox.left + localBoundingBox.width / 2.0f,
                                localBoundingBox.top + localBoundingBox.height / 2.0f);
    buttonBackground->setPosition(mPosition);

    mBoundingBox = buttonBackground->getGlobalBounds();

    screen.push_back(buttonBackground);


    //add text
    mButtonText->setPosition(mPosition);
    screen.push_back(mButtonText);
}
