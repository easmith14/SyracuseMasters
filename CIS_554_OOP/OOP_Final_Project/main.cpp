/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
Final Project: Snake
Last Updated: 3 / 29 / 21
This is the main program for the Snake game, which initializes the game manager,
and starts the refresh loop that drives the game.
*/

#include <SFML/Graphics.hpp>
#include <vector>
#include "SnakeGameManager.h"

using sf::Event;
using sf::Shape;
using sf::RenderWindow;
using sf::Mouse;
using sf::Drawable;
using sf::VideoMode;
using sf::ContextSettings;

using std::vector;

//store basic high-level constants here for ease of access
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;
const int FRAME_RATE = 4;
const int RESOLUTION = 100;

int main()  
{
    //set up the graphics window with appropriate settings
    ContextSettings settings;
    settings.antialiasingLevel = 8;

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Retro Snake", sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);

    //create overall game logic manager
    SnakeGameManager manager(WINDOW_WIDTH, WINDOW_HEIGHT, FRAME_RATE, RESOLUTION);

    //start the core event updating loop that drives the game
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                //handle the user closing the window
                window.close();
            }

            if (event.type == Event::MouseButtonPressed)
            {
                //send click location to the SnakeManager as last clicked location
                manager.HandleClick(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
            }

            if (event.type == Event::KeyPressed)
            {
                //send key that was pressed to SnakeManager to be queued for input
                manager.UpdateKeyPressQueue(event.key.code);
            }
        }

        //update screen to show current game situation. 
        //We use the virtual Drawable class to allow for all required graphics to be returned in a single vector. 
        //Polymorphism!
        window.clear();
        vector<Drawable*> gameScreen = manager.UpdateScreen();

        for (auto element : gameScreen)
        {
            window.draw(*element);
        }

        window.display();
    }
}