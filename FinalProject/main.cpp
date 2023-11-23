#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "constants.h"
using namespace std; 

sf::RenderWindow* BuildWindow() {

    sf::RenderWindow* windowPtr = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sorter 1000");
    return windowPtr;
}

int main()
{
    sf::RenderWindow* windowPtr = BuildWindow(); 
    sf::RenderWindow& window = *windowPtr; 

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event))
        {
            // allow window closure 
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }
}

