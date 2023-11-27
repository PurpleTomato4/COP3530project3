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

//merge function for mergesort... time complexity is O(n)
void merge(vector<Flights>& flights, int left, int middle, int right)
{
    int leftSize = middle - left + 1;
    int rightSize = right - middle;


    vector<Flights> leftArr(leftSize);
    vector<Flights> rightArr(rightSize);


    //fill the right and left vectors with the corresponding data
    for (int i = 0; i < leftSize; i++)
        leftArr[i] = flights[left + i];
    for (int j = 0; j < rightSize; j++)
        rightArr[j] = flights[middle + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    //compare data from left and right sub arrays and merge in the new sorted order
    while (i < leftSize && j < rightSize)
    {
        if (leftArr[i].efficiency >= rightArr[j].efficiency)
        {
            flights[k] = leftArr[i];
            i++;
        }
        else
        {
            flights[k] = rightArr[j];
            j++;
        }
        k++;
    }

    //copy remaining elements from left array
    while (i < leftSize)
    {
        flights[k] = leftArr[i];
        i++;
        k++;
    }

    //copy remaining elements from right array
    while (j < rightSize)
    {
        flights[k] = rightArr[j];
        j++;
        k++;
    }
}

//mergesort function... time complexity is O(nlog(n))
void mergeSort(vector<Flights>& flights, int left, int right)
{
    if (left < right)
    {
        int middle = (left + right) / 2;

        //recursively split the vector in half until base case
        mergeSort(flights, left, middle);
        mergeSort(flights, middle + 1, right);

        //merge the split vectors together
        merge(flights, left, middle, right);
    }
}

vector<Flights*> PullData() {
    vector<Flights*> flights;
    flights.reserve(120000);

    ifstream input("flightdata.csv");
    if (!input.is_open())
    {
        cout << "Error: File not detected." << endl;
        return flights; 
    }
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
        Flights* newFlight = new Flights(stof(seats), stof(passengers), name, stof(distance));
        flights.push_back(newFlight);
    }
    return flights; 
}

string flightsToString(const Flights& flight) {
    // Convert Flights data to a string
    string flightInfo = "Name: " + flight.name +
        " Seats: " + std::to_string(flight.seats) +
        " Passengers: " + std::to_string(flight.passengers) +
        " Distance: " + std::to_string(flight.distance) +
        " Efficiency: " + std::to_string(flight.efficiency);
    return flightInfo;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sorter 1000");

    vector<Flights*> data = PullData(); 
    /*vector<Flights*> data; 
    Flights* flight = new Flights();
    data.push_back(flight); */

    int scrollOffset = 0; 

    sf::Sprite flightSortSprite;
    sf::Sprite rawDataSprite;
    sf::Sprite testSprite1; 
    sf::Sprite testSprite2; 

    flightSortSprite.setTexture(TextureManager::GetTexture("AirlineSort")); // 309 x 88
    flightSortSprite.setPosition(LEFT_MENU_X, LEFT_MENU_Y);
    rawDataSprite.setTexture(TextureManager::GetTexture("SourceData")); // 309 x 88
    rawDataSprite.setPosition(RIGHT_MENU_X, RIGHT_MENU_Y);
    testSprite1.setTexture(TextureManager::GetTexture("testImage1"));
    testSprite1.setPosition(WIDTH / 2, HEIGHT / 2);
    testSprite2.setTexture(TextureManager::GetTexture("testImage2"));
    testSprite2.setPosition(WIDTH / 2, HEIGHT / 2);

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

                if (x >= 0 && x < WIDTH && y >= 0 && y < (RIGHT_MENU_Y + BUTTON_HEIGHT)) { 
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
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    if (scrollOffset > 0) {
                        scrollOffset -= 1; 
                    }
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    if (scrollOffset < static_cast<int>(data.size()) - NUM_VISIBLE_ROWS) {
                        scrollOffset += 1; 
                    }
                }
            }
        }
        for (int i = scrollOffset; i < scrollOffset + NUM_VISIBLE_ROWS && i < data.size(); i++) {
            sf::Font font;
            if (!font.loadFromFile("arial.ttf")) {
                cout << "No font file" << endl; 
                return EXIT_FAILURE;
            }
            sf::Text flightText;
            flightText.setFont(font);
            flightText.setString(flightsToString(*data[i]));
            flightText.setCharacterSize(14); 
            flightText.setPosition(10, (i - scrollOffset) * ROW_HEIGHT); 
            window.draw(flightText); 
        }

        window.display(); 
    }
    for (Flights* flight : data) {
        delete flight;
    }
    data.clear();
    return 0; 
}

