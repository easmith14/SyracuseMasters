/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
Final Project: Snake
Last Updated: 3 / 29 / 21
This file implements a toggle element, which is clickable and stores/displays state
*/
#include "MenuToggle.h"
#include "DrawingConstants.h"

using sf::Vector2f;
using sf::RectangleShape;
using sf::CircleShape;
using sf::Color;

//if clicked, check if the click was on this element
void MenuToggle::HandleClick(int x, int y) 
{
    //if clicked in box, toggle setting
    if (mBoundingBox.contains(Vector2f(x, y)))
    {
        mOwnedOption = !mOwnedOption;
    }
}

//add the toggle drawables to the screen
void MenuToggle::AddDrawables(vector<Drawable*>& screen)
{
    //make checkbox background
    RectangleShape* buttonBackground = new RectangleShape(Vector2f(mScreenWidth / DrwCnst::TOGGLE_WIDTH_FACTOR, 
                                                                   mScreenHeight / DrwCnst::TOGGLE_WIDTH_FACTOR));
    buttonBackground->setFillColor(Color::Transparent);
    buttonBackground->setOutlineColor(DrwCnst::DARK_ACCENT_COLOR);
    buttonBackground->setOutlineThickness(DrwCnst::TOGGLE_BORDER_THICKNESS);

    //center origin and record bounding box
    FloatRect localCheckboxBoundingBox = buttonBackground->getLocalBounds();
    buttonBackground->setOrigin(localCheckboxBoundingBox.left + localCheckboxBoundingBox.width / 2.0f,
        localCheckboxBoundingBox.top + localCheckboxBoundingBox.height / 2.0f);
    buttonBackground->setPosition(mPosition);

    mBoundingBox = buttonBackground->getGlobalBounds();

    //if toggled on, show an indicator inside the button
    if (mOwnedOption)
    {
        CircleShape* selectedIndicator = new CircleShape(localCheckboxBoundingBox.width / DrwCnst::TOGGLE_SELECTION_FACTOR);
        selectedIndicator->setFillColor(DrwCnst::TOGGLE_SELECTION_COLOR);
        selectedIndicator->setOutlineColor(DrwCnst::TOGGLE_ACCENT_COLOR);
        selectedIndicator->setOutlineThickness(DrwCnst::BUTTON_BORDER_THICKNESS);

        //center origin and position on center of check box
        FloatRect indicatorLocalBoundingBox = selectedIndicator->getLocalBounds();
        selectedIndicator->setOrigin(indicatorLocalBoundingBox.left + indicatorLocalBoundingBox.width / 2.0f,
            indicatorLocalBoundingBox.top + indicatorLocalBoundingBox.height / 2.0f);

        selectedIndicator->setPosition(Vector2f(buttonBackground->getPosition()));
        buttonBackground->setFillColor(DrwCnst::TOGGLE_FILL_COLOR);
        screen.push_back(selectedIndicator);
    }

    screen.push_back(buttonBackground);

    //add text off to the right side
    FloatRect textLocalBoundingBox = mButtonText->getLocalBounds();
    mButtonText->setPosition(mPosition + Vector2f(textLocalBoundingBox.width, 0.0f));
    screen.push_back(mButtonText);
}
