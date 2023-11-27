#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Flights.h"
#include "TextureManager.h"
#include "constants.h"
using namespace std; 

vector<Flights> PullData() {
    vector<Flights> flights;
    ifstream input("flightdata.csv");
    if (!input.is_open())
    {
        cout << "Error: File not detected." << endl;
    }
    else {
        string line;
        getline(input, line);
        while (getline(input, line))
        {
            istringstream stream(line);
            //anytime get line is used with token it is just to skip past that piece of data
            string token;
            string departures;
            string seats;
            string passengers;
            string distance;
            string name;
            
            getline(stream, token, ',');
            getline(stream, departures, ',');
            getline(stream, token, ',');
            getline(stream, seats, ',');
            getline(stream, passengers, ',');

            for (int i = 0; i < 7; i++)
            {
                if (i == 2) {
                    getline(stream, distance, ',');
                }
                else {
                    getline(stream, token, ',');
                }
            }
            getline(stream, name, ',');
            Flights newFlight = Flights(stof(seats), stof(passengers), name, stof(distance));
            flights.push_back(newFlight);
        }
    }
    return flights; 
}

sf::RenderWindow* BuildWindow() {

    sf::RenderWindow* windowPtr = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sorter 1000");
    return windowPtr;
}

int main()
{
    sf::RenderWindow* windowPtr = BuildWindow(); 
    sf::RenderWindow& window = *windowPtr; 

    sf::Sprite flightSortSprite;
    sf::Sprite rawDataSprite;
    sf::Sprite testSprite1; 
    sf::Sprite testSprite2; 

    flightSortSprite.setTexture(TextureManager::GetTexture("AirlineSort"));
    flightSortSprite.setPosition(LEFT_MENU_X, LEFT_MENU_Y);
    rawDataSprite.setTexture(TextureManager::GetTexture("SourceData"));
    rawDataSprite.setPosition(RIGHT_MENU_X, RIGHT_MENU_Y);
    testSprite1.setTexture(TextureManager::GetTexture("testImage1"));
    testSprite1.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    testSprite2.setTexture(TextureManager::GetTexture("testImage2"));
    testSprite2.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    bool displayTest1 = false; 
    bool displayTest2 = false; 

    while (window.isOpen()) {

        //window.clear(); 
        sf::Event event;
        while (window.pollEvent(event))
        {
            //window.clear(); // Clear the window

            // Draw sprites
            window.draw(flightSortSprite);
            window.draw(rawDataSprite);

            window.display(); 

            // allow window closure 
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                auto mousePosition = sf::Mouse::getPosition(window);
                int x = mousePosition.x;
                int y = mousePosition.y;

                if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        // determine what sprite is being clicked
                        if (flightSortSprite.getGlobalBounds().contains(x, y)) {
                            displayTest1 = true; 
                            cout << "Flight sort sprite" << endl; 
                        }
                        if (rawDataSprite.getGlobalBounds().contains(x, y)) {
                            displayTest2 = true; 
                            cout << "Raw data sprite" << endl; 
                        }
                    }
                }
            }
            /*window.clear(); 
            if (!displayTest1 && !displayTest2) {
                window.draw(flightSortSprite);
                window.draw(rawDataSprite);
            }
            else if (displayTest1 && !displayTest2) {
                window.draw(testSprite1);
            }
            else if (!displayTest1 && displayTest2) {
                window.draw(testSprite2); 
            }*/
        }
        window.display(); 
    }
    delete windowPtr; 
    return 0; 
}

