/** COP3530 Project 3 - Airline Sorter 1000
 ** University of Florida - Fall 2023
 ** Authors: Jack Goldstein, Benjamin Uppgard, Ryan Wilson
 ** Date: 12/07/2023
 **/

#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <iomanip>
#include "FlightData.h"
using namespace std;

/*** Destructor ***/
FlightData::~FlightData() {
    for (auto i : _flightData)
        delete i;
    for (auto i : _airCarrierData)
        delete i;
    for (auto i : _cityPairs)
        delete i;
}

/*** Public Functions ***/
void FlightData::LoadData(string filename) {
    // Open the file
    ifstream input(filename);
    if (!input.is_open()) {
        cout << "Error: File not detected." << endl;
    } else {
        // Upon successfully opening the file, read the first row
        string line;
        getline(input, line);
        // Process each column of the row
        while (getline(input, line)) {
            istringstream stream(line);
            // Anytime get line is used with token it is just to skip past that
            // piece of data
            string token;
            string seats;
            string passengers;
            string carrier;
            string origin;
            string destination;
            string distance;

            for (int i = 0; i < 3; i ++)
                getline(stream, token, ',');

            getline(stream, seats, ',');
            getline(stream, passengers, ',');

            for (int i = 0; i < 2; i ++)
                getline(stream, token, ',');

            getline(stream, distance, ',');

            for (int i = 0; i < 4; i ++)
                getline(stream, token, ',');

            getline(stream, carrier, ',');

            for (int i = 0; i < 9; i ++)
                getline(stream, token, ',');

            getline(stream, token, '"');

            getline(stream, origin, '"');

            getline(stream, token, '"');

            getline(stream, destination, '"');

            // Ignore outlier flights with distance of "0"
            if (stoi(distance) > 0) {
                Flights *newFlight = new Flights(carrier, origin, destination,
                                                 stoi(seats), stoi(passengers),
                                                 stoi(distance));
                _flightData.push_back(newFlight);
            }
        }
    }
    // Populate the Carrier Data  and City Pair vectors
    GetCityPairs();
    GetCarrierData();
}

// Data Print Functions
void FlightData::PrintCarrierTop20() {
    // Minimum field widths
    int field_one_width = 10;
    // Iterate through the first 20 data elements, update the first field width
    for (int i = 0; i < 20; i++) {
        if (_airCarrierData[i]->_carrier.length() > field_one_width)
            field_one_width = _airCarrierData[i]->_carrier.length();
    }
    // Print the first 20 data elements
    for (int i = 0; i < 20; i++) {
        cout << setw(2) << right << i + 1 << ". " << "Airline: " <<
             setw(field_one_width) << left << _airCarrierData[i]->_carrier
             << " | Efficiency: " << fixed << setprecision(3)
             << _airCarrierData[i]->_efficiency << endl;
    }
    cout << endl;
}

void FlightData::PrintCityPairTop20() {
    // Minimum field widths
    int field_one_width = 10;
    int field_two_width = 10;
    // Iterate through the first 20 data elements, update city field widths
    for (int i = 0; i < 20; i++) {
        if (_cityPairs[i]->_origin.length() > field_one_width)
            field_one_width = _cityPairs[i]->_origin.length();
        if (_cityPairs[i]->_destination.length() > field_two_width)
            field_two_width = _cityPairs[i]->_destination.length();
    }
    // Print the first twenty elements
    for (int i = 0; i < 20; i++) {
        cout << setw(2) << left << i + 1 << ". " << "Origin: " <<
             setw(field_one_width) << left << _cityPairs[i]->_origin <<
             "  Destination: " << setw(field_two_width) << left <<
             _cityPairs[i]->_destination
             << " | Efficiency: " << fixed << setprecision(3)
             << _cityPairs[i]->_efficiency << endl;
    }
    cout << endl;
}

void FlightData::PrintDistanceTop20() {
    // Default field widths
    int field_one_width = 10;
    int field_two_width = 10;
    // Iterate through the first 20 elements. Resize widths as needed
    for (int i = 0; i < 20; i++) {
        if (_flightData[i]->_origin.length() > field_one_width)
            field_one_width = _flightData[i]->_origin.length();
        if (_flightData[i]->_destination.length() > field_two_width)
            field_two_width = _flightData[i]->_destination.length();
    }
    // Print the first 20 elements
    for (int i = 0; i < 20; i++) {
        cout << setw(2) << left << i + 1 << ". " << "Origin: " <<
             setw(field_one_width) << left << _flightData[i]->_origin <<
             "  Destination: " << setw(field_two_width) << left <<
             _flightData[i]->_destination <<
             "| Distance: " << _flightData[i]->_distance << endl;
    }
    cout << endl;
}

// Create a dedicated vector from the source data that groups flights from
// each carrier into a single entry
void FlightData::GetCarrierData() {

    unordered_map<string, Flights*> carrierMap;
    // Iterate through the data set and insert into the temporary map data
    // structure as needed
    for (auto i : _flightData) {
        Flights* copy = new Flights(i->_carrier, "", "", i->_seats, i->_passengers, 0);
        if (carrierMap.find(copy->_carrier) == carrierMap.end()) {
            carrierMap[copy->_carrier] = copy;
        }
        else {
            carrierMap[copy->_carrier]->_passengers += copy->_passengers;
            carrierMap[copy->_carrier]->_seats += copy->_seats;
            int seatTotal = carrierMap[copy->_carrier]->_seats;
            int passTotal = carrierMap[copy->_carrier]->_passengers;
            carrierMap[copy->_carrier]->_efficiency =
                    static_cast<float>(passTotal) / seatTotal;
        }
    }
    // When done, copy the map into a vector
    for (auto i : carrierMap) {
        // Ignore carriers that have flown less than 1000 passengers
        if (i.second->_passengers > 1000)
            _airCarrierData.push_back(i.second);
    }
}

// Create a dedicated vector from the source data that groups flights by
// the origin and destination cities
void FlightData::GetCityPairs() {
    unordered_map<string, Flights*> pairsMap;
    // Iterate through the data set and insert into the temporary map data
    // structure as needed
    for (auto i : _flightData) {
        string cityPair = i->_origin + " " + i->_destination;
        Flights* copy = new Flights("", i->_origin, i->_destination, i->_seats, i->_passengers, i->_distance);
        if (pairsMap.find(cityPair) == pairsMap.end()) {
            pairsMap[cityPair] = copy;
        }
        else {
            pairsMap[cityPair]->_passengers += copy->_passengers;
            pairsMap[cityPair]->_seats += copy->_seats;
            int seatTotal = pairsMap[cityPair]->_seats;
            int passTotal = pairsMap[cityPair]->_passengers;
            pairsMap[cityPair]->_efficiency =
                    static_cast<float>(passTotal) / seatTotal;
        }
    }
    // When done, copy the map into a vector. NOTE: Routes with less than 1000
    // passengers flown are ignored.
    for (auto i : pairsMap) {
        if (i.second->_passengers > 1000)
            _cityPairs.push_back(i.second);
    }
}
