#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Flights.h"
#include <SFML/Graphics.hpp>
#include "constants.h"
using namespace std; 

void PullData() {
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
}

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
            if (event.type == sf::Event::MouseButtonPressed) {
                auto mousePosition = sf::Mouse::getPosition(window);
                int x = (mousePosition.x) / 32;
                int y = (mousePosition.y) / 32;
            }
        }
    }
}

